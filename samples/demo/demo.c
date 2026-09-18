#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "pdfsolid_common_c.h"
#include "pdfsolid_conversion_c.h"

int main(int argc, char **argv) {
    char version[64] = {0};
    char model[4096];
    struct stat info;
    CPDF_GetVersion(version);
    printf("sdk_version=%s\n", version);
    if (strcmp(version, "1.2.0") != 0) return 1;
    if (argc == 2 && strcmp(argv[1], "--version") == 0) return 0;
    if (argc != 5) {
        fprintf(stderr, "Usage: demo <license.xml> <resource-dir> <input.pdf> <new-output.docx>\n");
        return 2;
    }
    int length = snprintf(model, sizeof(model), "%s/models/documentai.model", argv[2]);
    if (length < 0 || length >= sizeof(model) || stat(argv[1], &info) != 0 ||
        stat(model, &info) != 0 || stat(argv[3], &info) != 0 || stat(argv[4], &info) == 0) return 2;
    int code = (int)CPDF_LicenseVerify(argv[1], "", "");
    printf("license_return_code=%d\n", code);
    if (code != 0) { CPDF_Release(); return 3; }
    CPDF_Initialize(argv[2]);
    code = (int)CPDF_SetDocumentAIModel(model, -1);
    printf("model_return_code=%d\n", code);
    if (code != 0) { CPDF_Release(); return 4; }
    CConvertOption options = CPDF_CONVERT_OPTION_DEFAULT;
    code = (int)CPDF_StartPDFToWord(argv[3], "", argv[4], options, NULL);
    printf("conversion_return_code=%d\n", code);
    CPDF_Release();
    if (code != 0) return 5;
    if (stat(argv[4], &info) != 0 || info.st_size <= 0) return 6;
    printf("output_bytes=%lld\n", (long long)info.st_size);
    return 0;
}
