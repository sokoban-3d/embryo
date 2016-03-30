#include <assert.h>
#include <unistd.h>
#include <stdio.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "err/abort_because.h"

#include "fs/fwrite_ptr.h"
#include "fs/fwrite_scalar.h"

int main(int argc, char **argv) {
    if(argc != 2 && argc != 3) {
        abort_because("Bad argument count.");
    }

    char *in = argv[1];

    Assimp::Importer importer;

    auto scene = importer.ReadFile(
        in, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices
    );

    if(!scene) {
        abort_because("%s", importer.GetErrorString());
    }

    if(scene->mNumMeshes == 0) {
        // TODO: Why doesn't importer.ReadFile fail instead?
        abort_because("%s has an unsupported model format.", in);
    }

    if(argc >= 3) {
        char *out = argv[2];

        errno = 0;

        chdir(out);

        if(errno) {
            abort_because(
                "Cannot change into %s: %s.", out, strerror(errno)
            );
        }
    }

    auto has_tex = false;

    for(auto im = 0; im < scene->mNumMeshes; ++im) {
        auto m = scene->mMeshes[im];

        if(m->HasTextureCoords(1)) {
            abort_because(
                "Mesh #%d has more than 1 UV set (unsupported).",
                im + 1
            );
        }

        if(m->HasTextureCoords(0)) {
            has_tex = true;

            break;
        }
    }

    {
        auto xyzfmt_f = fopen("xyzfmt", "w");

        fputs(has_tex? "xyz uv\n" : "xyz\n", xyzfmt_f);

        fclose(xyzfmt_f);
    }

    auto xyz_f = fopen("xyz", "wb");
    auto idx_f = fopen("idx", "wb");
    auto idxtab_f = fopen("idxtab", "w");

    auto xyzWritten = 0;
    auto idxWritten = 0;

    for(auto im = 0; im < scene->mNumMeshes; ++im) {
        auto m = scene->mMeshes[im];

        auto mFirstXyzIdx = xyzWritten;

        for(auto iv = 0; iv < m->mNumVertices; ++iv, ++xyzWritten) {
            s3d_fwrite_ptr(&m->mVertices[iv].x, 3, xyz_f);

            if(has_tex) {
                s3d_fwrite_ptr(&m->mTextureCoords[0][iv].x, 2, xyz_f);
            }
        }

        auto mFirstIdxIdx = idxWritten;
        auto mIdxWritten = 0;

        for(auto ifa = 0; ifa < m->mNumFaces; ++ifa) {
            auto face = m->mFaces[ifa];

            assert(face.mNumIndices == 3);

            for(
                auto ii = 0;
                ii < 3;
                ++ii, ++idxWritten, ++mIdxWritten
            ) {
                s3d_fwrite_scalar(
                    mFirstXyzIdx + face.mIndices[ii], idx_f
                );
            }
        }

        fprintf(idxtab_f, "%d %d\n", mFirstIdxIdx, mIdxWritten);
    }

    fclose(xyz_f);
    fclose(idx_f);
    fclose(idxtab_f);

    // TODO: Prevent Assimp from generating this file.
    unlink("dna.txt");

    return 0;
}
