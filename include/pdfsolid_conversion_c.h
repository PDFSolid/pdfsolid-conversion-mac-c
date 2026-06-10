#ifndef PDFSOLID_CONVERSION_C_H
#define PDFSOLID_CONVERSION_C_H

#if _WIN32
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "pdfsolid_basictypes_c.h"

/// \brief Starts the conversion of a PDF file to a Word document.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \\param[in] output_path Path where the converted Word document will be saved.
/// \\param[in] options \link CConvertOption \endlink settings for conversion.
/// \\param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToWord(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

/// \brief Starts the conversion of a PDF file to an RTF document.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \param[in] output_path Path where the converted RTF document will be saved.
/// \param[in] options \link CConvertOption \endlink settings for conversion.
/// \param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToRtf(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

/// \brief Starts the conversion of a PDF file to an Excel document.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \param[in] output_path Path where the converted Excel document will be saved.
/// \param[in] options \link CConvertOption \endlink settings for conversion.
/// \param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToExcel(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

/// \brief Starts the conversion of a PDF file to a PowerPoint presentation.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \param[in] output_path Path where the converted PowerPoint presentation will be saved.
/// \param[in] options \link CConvertOption \endlink settings for conversion.
/// \param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToPpt(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

/// \brief Starts the conversion of a PDF file to an HTML document.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \param[in] output_path Path where the converted HTML document will be saved.
/// \param[in] options \link CConvertOption \endlink settings for conversion.
/// \param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToHtml(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

/// \brief Starts the conversion of a PDF file to an image format.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \param[in] output_path Path where the converted images will be saved.
/// \param[in] options \link CConvertOption \endlink settings for conversion.
/// \param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToImage(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

/// \brief Starts the conversion of a PDF file to a searchable PDF.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \param[in] output_path Path where the searchable PDF will be saved.
/// \param[in] options \link CConvertOption \endlink settings for conversion.
/// \param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToSearchablePDF(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

/// \brief Starts the conversion of a PDF file to a plain text file.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \param[in] output_path Path where the converted text file will be saved.
/// \param[in] options \link CConvertOption \endlink settings for conversion.
/// \param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToTxt(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

/// \brief Starts the conversion of a PDF file to a JSON file.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \param[in] output_path Path where the converted JSON file will be saved.
/// \param[in] options \link CConvertOption \endlink settings for conversion.
/// \param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToJson(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

/// \brief Starts the conversion of a PDF file to a Markdown file.
///
/// \param[in] file_path Path to the input PDF file.
/// \param[in] password Password for opening the PDF file (if required).
/// \param[in] output_path Path where the converted JSON file will be saved.
/// \param[in] options \link CConvertOption \endlink settings for conversion.
/// \param[in] callback Optional \link CConvertCallback \endlink function for handling convert operations.
/// \return \link CSDKErrorCode \endlink indicating the success or failure of the operation.
PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToMarkdown(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);


PDFSOLID_DECL
CSDKErrorCode CSDK_PDFSOLID_CALL CPDF_StartPDFToOfd(PDFSOLID_STRING file_path, PDFSOLID_STRING password, PDFSOLID_STRING output_path, CConvertOption options, CConvertCallback* callback);

#ifdef __cplusplus
}

#endif

#endif //PDFSOLID_CONVERSION_C_H
