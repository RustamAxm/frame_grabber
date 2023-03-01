#include <Windows.h>
#pragma once
//ALIASES += "sample=\par \"Sample code\""

//////////////////////////////////////////////////////
/// \defgroup flex_ref FrameLink Express Reference
/// \ingroup flex
/// The following elements are used with FrameLink Express
///@{
//////////////////////////////////////////////////////

#ifndef VCECLB_H
#define VCECLB_H

#pragma pack(push,4)

#ifndef DOXYGEN_SHOULD_SEE_THIS
/// Declare export function macros
#ifdef VCECLB_SDK_EXPORTS
#define VCECLB_SDK_API __declspec(dllexport)
#else
#define VCECLB_SDK_API //__declspec(dllimport)
#endif

/// Declare calling convention macros
#define VCECLB_CALL __stdcall

#endif


//////////////////////////////////////////////////////
/// \defgroup flex_enum FrameLink Express Enumerations
/// The following enumerations are used in FrameLink Express
///@{
//////////////////////////////////////////////////////


/// Error codes returned by FrameLink functions
typedef enum tagVCECLB_Error {
	VCECLB_Err_Success = 0, /**< Operation successful */
	VCECLB_Err_noDriver, /**< Driver is not installed */
	VCECLB_Err_noDevicePresent, /**< Device is not present */
	VCECLB_Err_notInitialized,  /**< Frame grabber has not been initialized */
	VCECLB_Err_noMemory, /**< Not enough memory to perform operation */
	VCECLB_Err_badArgument, /**< Argument is invalid */
	VCECLB_Err_notPrepared, /**< Frame grabber has not been prepared
				            * to perform grabbing operations
							*/
	VCECLB_Err_notGrabbed, /**< Image has not been grabbed yet */
	VCECLB_Err_bufferBusy, /**< Requested buffer has not been released */
	VCECLB_Err_lostContact, /**< Camera stops streaming images */
	VCECLB_Err_SnapTimeout = VCECLB_Err_lostContact,  /**< Snap image timed out */
	VCECLB_Err_cameraNotConnected, /**< Camera is not connected
									* or not powered on
									*/
	VCECLB_Err_UART_Timeout, /**< Time-out occurs during UART operation */
	VCECLB_Err_UART_Error, /**< Error occurs during UART operation */
	VCECLB_Err_DeviceBusy, /**< Device busy or not responding */
	VCECLB_Err_NoMoreItems, /**< Image buffer queue is full */
	VCECLB_Err_notSupported = 254, /**< Operation is not supported */
	VCECLB_Err_UnknownError = 255, /**< Unknown (system) error occurs */
} VCECLB_Error;

/// Frame grabber capabilities
/** \see 
* VCECLB_GetCapability()
*/
typedef enum tagVCECLB_Capability
{
	VCECLB_Cap_PoCL = 0, /**< Power over CameraLink capability */
	VCECLB_Cap_PLC, /**< Programmable Logic Controller capability */
	VCECLB_Cap_FullDeca, /**< Full/Deca configuration capability */
	VCECLB_Cap_DualChannels /**< Dual CameraLink channels capability */
} VCECLB_Capability;

/// Predefined tap configuration
/** \see
* VCECLB_IsTapConfigPredefined()
* VCECLB_GetPredefinedTapConfig()
*/
typedef enum tagVCECLB_TapConfigPredefined
{
	VCECLB_TapConfig_Custom = 0, /**< Custom tap configuration */
	VCECLB_TapConfig_1TapLR, /**< One tap left to right configuration */
	VCECLB_TapConfig_1TapRL, /**< One tap right to left
							 * (inversed) configuration
							 */
	VCECLB_TapConfig_2TapInterLR, /**< Two taps interleaved
								  * left to right configuration
								  */
	VCECLB_TapConfig_2TapInterRL, /**< Two taps interleaved
								  * right to left configuration
								  */
	VCECLB_TapConfig_2TapSepLR, /**< Two taps separated
								* left to right configuration
								*/
	VCECLB_TapConfig_2TapSepRL, /**< Two taps separated
								* right to left configuration
								*/
	VCECLB_TapConfig_2TapSepConv, /**< Two taps separated
								  * convergence configuration
								  */
	VCECLB_TapConfig_2TapSepDiv, /**< Two taps separated
								 * divergence configuration
								 */
	VCECLB_TapConfig_3TapSepLR, /**< Three taps separated
								* left to right configuration
								*/
	VCECLB_TapConfig_4TapSepLR, /**< Four taps separated
								* left to right configuration
								*/
	VCECLB_TapConfig_4TapSepRL, /**< Four taps separated
								* right to left configuration
								*/
	VCECLB_TapConfig_4Tap2SegLR, /**< Four taps separated
								 * two segments by two elements
								 * left to right configuration
								 */
	VCECLB_TapConfig_4Tap2SegConv, /**< Four taps separated
								   * two segments by two elements
								   * left to right convergence configuration
								   */
	VCECLB_TapConfig_4TapQuadConv, /**< Four taps quadrate
								   * convergence configuration
								   */
	VCECLB_TapConfig_4TapInterLR, /**< Four taps interleaved
								  * left to right configuration
								  */
	VCECLB_TapConfig_4TapInterRL, /**< Four taps interleaved
								  * right to left configuration
								  */
	VCECLB_TapConfig_8TapInterLR, /**< Eight taps interleaved
								  * left to right configuration
								  */
	VCECLB_TapConfig_10TapInterLR, /**< Ten taps interleaved
								  * left to right configuration
								  */
} VCECLB_TapConfigPredefined;

/// Camera control strobe configuration
typedef enum tagVCECLB_EX_CC_State {
	VCECLB_EX_CC_LOW=0, /**< Logical Zero state */
	VCECLB_EX_CC_HIGH, /**< Logical One state */
	VCECLB_EX_CC_MASTER_PULSE, /**< Master pulse generator state */
	VCECLB_EX_CC_MASTER_INVPULSE, /**< Inverted master pulse generator */
	VCECLB_EX_CC_SLAVE_PULSE, /**< Slave pulse generator state */
	VCECLB_EX_CC_SLAVE_INVPULSE, /**< Inverted Slave pulse generator */
	VCECLB_EX_CC_OC_MASTER_PULSE, /**< Opposite port master pulse generator state */
	VCECLB_EX_CC_OC_MASTER_INVPULSE, /**< Opposite port inverted master pulse generator */
	VCECLB_EX_CC_OC_SLAVE_PULSE, /**< Opposite port slave pulse generator state */
	VCECLB_EX_CC_OC_SLAVE_INVPULSE, /**< Opposite port inverted Slave pulse generator */
} VCECLB_EX_CC_State;

/// Device type identificator
typedef enum tagVCECLB_DeviceType {
	VCECLB_DT_FrameLink, /**< FrameLink cardbus controller */
	VCECLB_DT_FrameLink_EX, /**< FrameLink Express card controller */
//	VCECLB_DT_FrameLink_PCIEx = VCECLB_DT_FrameLink_EX, /**< FrameLink PCI-Express controller with PLC and PoCL */
	VCECLB_DT_Unknown = -1, /**< Unknown controller */
} VCECLB_DeviceType;

///@}

/////////////////////////////////////////////////////////
/// \defgroup flex_struct FrameLink Express Structures
/// The following structures are used in FrameLink Express
///@{
/////////////////////////////////////////////////////////

/// Device initialization data
/**
* \note
* Internal usage only. Do not modify it.
*/
typedef struct tagVCECLB_DeviceData {
	unsigned long  cbSize; /**< Size of the structure*/
	char   DevicePath[1]; /**< Internal data*/
} VCECLB_DeviceData;

/// Device description information
typedef struct tagVCECLB_EnumData {
	unsigned long cbSize;	/**< Size of the structure.\n*/
			/**< Should be initialized to <c>sizeof(VCECLB_EnumData)</c>*/
			/**< before passing to VCECLB_EnumNext() function*/
	unsigned long dwSlot; /**< System defined slot number*/
	VCECLB_DeviceData* pDeviceData; /**< pointer to the device initialization data*/
	char* pSlotName; /**< pointer to the system defined slot name*/
} VCECLB_EnumData;

/// Tap reconstruction configuration
/**
* \note
* Number of camera output taps is product of <c>channels</c> and <c>taps</c>
*/
typedef struct tagVCECLB_TapConfig
{
	unsigned char channels; /**< Number of input channels (1 or 2) */
	unsigned char channelOrder; /**< Order of channel:
					   *<table>
					   *<tr><th>value</th><th>meaning</th></tr>
					   *<tr><td>TCCR_NORMAL</td><td>Normal channel order TCCR_NORMAL</td></tr>
					   *<tr><td>TCCR_REVERSE</td><td>Reversed channel order TCCR_REVERSE</td></tr>
					   *</table>
					   */
	unsigned char channelOutput; /**< Format of channels output:
						*<table>
					    *<tr><th>value</th><th>meaning</th></tr>
					    *<tr><td>TCCP_SEGMENTED</td><td>Segmented channel output TCCP_SEGMENTED</td></tr>
					    *<tr><td>TCCP_INTERLEAVED</td><td>Interleaved (Interlaced) channel output TCCP_INTERLEAVED</td></tr>
					    *</table>
					    */
	unsigned char channelDirection[2]; /**< Channel direction:
							  *<table>
							  *<tr><th>value</th><th>meaning</th></tr>
							  *<tr><td>TCCD_TOP_DOWN</td><td>Top-Down channel direction TCCD_TOP_DOWN</td></tr>
							  *<tr><td>TCCD_BOTTOM_UP</td><td>Bottom-up channel direction TCCD_BOTTOM_UP</td></tr>
							  *</table>
					    	  */
	unsigned char taps; /**< Number of taps per channel (1 to 4) */
	unsigned char tapOutput;	/**< Format of taps output
					*<table>
					*<tr><th>value</th><th>meaning</th></tr>
					*<tr><td>TCTO_SEGMENTED</td><td>Segmented tap output TCTO_SEGMENTED</td></tr>
					*<tr><td>TCTO_ALTERNATE</td><td>Alternated tap output. Two interleaved taps per segment TCTO_ALTERNATE</td></tr>
					*<tr><td>TCTO_INTERLEAVED</td><td>Interleaved tap output TCTO_INTERLEAVED</td></tr>
					*</table>
					*/
	unsigned char tapDirection[4]; /**< Tap direction:
						  *<table>
						  *<tr><th>value</th><th>meaning</th></tr>
						  *<tr><td>TCTD_LEFT_RIGHT</td><td>Left-Right tap direction TCTD_LEFT_RIGHT</td></tr>
						  *<tr><td>TCTD_RIGHT_LEFT</td><td>Right-Left tap direction TCTD_RIGHT_LEFT</td></tr>
						  *</table>
					      */
} VCECLB_TapConfig;

#ifndef DOXYGEN_SHOULD_SEE_THIS

/// Order of channel
#define TCCR_NORMAL  0	/**< Normal channel order */
#define	TCCR_REVERSE 1	/**< Reversed channel order */

///Format of channels output
#define TCCP_SEGMENTED   0 /**< Segmented channel output*/
#define TCCP_INTERLEAVED 1 /**< Interleaved (Interlaced) channel output*/

///Channel direction
#define TCCD_TOP_DOWN	0 /**< Top-Down channel direction */
#define TCCD_BOTTOM_UP	1 /**< Bottom-up channel direction */

///Format of taps output
#define TCTO_SEGMENTED	0 /**< Segmented tap output */
#define TCTO_ALTERNATE	1 /**< Alternated tap output. Two interleaved taps per segment */
#define TCTO_INTERLEAVED	2 /**< Interleaved tap output */

///Tap direction
#define TCTD_LEFT_RIGHT	0 /**< Left-Right tap direction */
#define TCTD_RIGHT_LEFT	1 /**< Right-Left tap direction */

#endif

/// Frame grabber configuration settings
/**
*\note
* Image width that camera produces should be equal to sum of
* <c>WidthPreValid</c>, <c>Width</c> and <c>WidthPostValid</c>
*
* Image height that camera produces should be equal to sum of
* <c>HeightPreValid</c>, <c>Height</c> and <c>HeightPostValid</c>
*/
typedef struct tagVCECLB_CameraDataEx
{
	unsigned long WidthPreValid; /**< Number of pixels at start of line to ignore */
	unsigned long Width; /**< Width of output image line */
	unsigned long WidthPostValid; /**< Number of pixels at end of line to ignore */
	unsigned long HeightPreValid; /**< Number of lines at start of image to ignore */
	unsigned long Height; /**< Number of lines in output image */
	unsigned long HeightPostValid; /**< Number of lines at end of image to ignore */
	unsigned long BitDepth; /**< Camera output bit depth */
	unsigned long Packed; /**< Packing settings.
				  * - 0 - Do not pack data (better CPU performance)
				  * - 1 - Pack data (better bandwidth utilization)
				  */
	VCECLB_TapConfig TapConfig; /**< Tap reconstruction settings */
	unsigned long SwapTaps; /**< Swap taps for dual tap output. */
	unsigned long IgnoreDVAL; /**< Ignore DataValid signal */
	unsigned long InvertDVAL; /**< DataValid signal is inverted */
	unsigned long InvertLVAL; /**< LineValid signal is inverted */
	unsigned long InvertFVAL; /**< FrameValid signal is inverted */
	unsigned long LineScan; /**< LineScan camera */
} VCECLB_CameraDataEx;

/// Acquired frame information
/**
*\note
* Image buffer size is calculted from width, height and bitdepth
* rounded up to the next page size (4KB).
*
* E.g. for image 1000x1000\@12bit the image size is:
*
* <c>1000(pixels)*1000(lines)*2(byte for 12bits) = 2 000 000 = 488*4096+1152</c>
*
* So alocated buffer size will be <c>489*4096 = 2 002 944</c>
*/
typedef struct tagVCECLB_FrameInfoEx
{
	unsigned long number; /**< Number of the frame, since start of the grabbing */
	unsigned long timestamp; /**< Timestamp in microseconds (uSecs), since start of the grabbing */
	void* lpRawBuffer; /**< Pointer to buffer with raw image data */
	unsigned long bufferSize; /**< Size of the raw image buffer */
	unsigned long  dma_status; /**< DMA status of the captured image */
} VCECLB_FrameInfoEx;

#ifndef DOXYGEN_SHOULD_SEE_THIS

///DMA Status codes:
#define VCECLB_DMA_STATUS_OK           0 /**< Frame acquired successfully */
#define VCECLB_DMA_STATUS_FRAME_DROP  0x00000001 /**< Frame was dropped */
#define VCECLB_DMA_STATUS_FIFO_OVERRUN 0x00000002 /**< FIFO Overrun occurs */
#define VCECLB_DMA_STATUS_ABORTED      0x00000010 /**< Frame acquiring was aborted */
#define VCECLB_DMA_STATUS_DICONNECTED  0x00000020 /**< Camera disconnected */

#endif

/// Camera control strobes configuration
typedef struct tagVCECLB_CCStrobesEx
{
	VCECLB_EX_CC_State cc[4]; /**< Array of the camera control strobes */
} VCECLB_CCStrobesEx;

/// Pulse generator configuration
/**
*\note
* <c>MasterWidth</c> should be less then <c>MasterPeriod</c>.
*
* <c>SlaveWidth</c> should be less then <c>MasterPeriod</c>.
*
* <c>SlaveDelay</c> should be less then <c>MasterPeriod</c>.
*
* <c>MasterPeriod</c>, <c>MasterWidth</c>, <c>SlaveWidth</c>
* and <c>SlaveDelay</c> uses <c>PulseGranularity</c> units
*/
typedef struct tagVCECLB_PulseGeneratorEx
{
	unsigned char	PulseLimited; /**< Do limit the number of the pulses to generate */
	unsigned short	PulseCount; /**< If the number of the pulses is limited: Limit value, otherwise not used */
	unsigned short	PulseGranularity; /**< Pulse granularity in 10 nanoseconds (nSecs) */
	unsigned short	MasterWidth; /**< Width of the master pulse generator signal in granularity units*/
	unsigned short	MasterPeriod; /**< Period of the master pulse generator signal in granularity units*/
	unsigned short	SlaveWidth; /**< Width of the slave pulse generator signal in granularity units*/
	unsigned short	SlaveDelay; /**< Delay of the slave pulse generator signal from the master pulse in granularity units*/
} VCECLB_PulseGeneratorEx;

/**
* \ingroup flex_func_imaq
*/
/// Application-defined callback function that recieves information about acquired frame.
/**
*@param lpUserData User supplied data
*@param pFrameInfo Information about acquired frame
* \sample
* \code
* void __stdcall GrabFrame_CallBackEx(void* lpUserData, VCECLB_FrameInfoEx* pFrameInfo)
* {
*   // Process incoming frame
* }
* ...
* VCECLB_StartGrabEx(hDevice, nPort, 0, &GrabFrame_CallBackEx, NULL);
* ...
* \endcode
*/
#ifdef DOXYGEN_SHOULD_SEE_THIS
void GrabFrame_CallBackEx(void* lpUserData, VCECLB_FrameInfoEx* pFrameInfo);
#endif /* DOXYGEN_SHOULD_SEE_THIS */


/// Type definition for Application-defined callback function
/**
* See GrabFrame_CallBackEx() for more information
*/
typedef void (__stdcall *VCECLB_GrabFrame_CallbackEx)(void* lpUserData, VCECLB_FrameInfoEx* pFrameInfo);


/// Image acquisition statistical information
typedef struct tagVCECLB_GrabStatEx
{
	unsigned int FrameRate; /**< Number of the frames received from the CameraLink interface during a 1 second period */
	unsigned int ClockRate; /**< The rate of the clocks received over the Camera Link interface. */
	unsigned int Horiz; /**< Number of the pixels per lines as determined by the card's CameraLink interface. 
						Note that this does not account for single vs. dual tap mode. */
	unsigned int Vert; /**< Number of the lines per frame as determined by the card's CameraLink interface. */

	unsigned int GrabRate; /**< Number of the frames acquired within a 1 second period. */
	unsigned int GrabCount /**< Number of the frames that have acquired since the last time VCECLB_StartGrabEx() has been called. */;
	unsigned int DropCount; /**< Number of dropped frames. */
	unsigned int OverrunCount; /**< Number of FIFO overruns. */
} VCECLB_GrabStatEx;

/// Raw pixel description structure
/**
*\note
* <c>cameraData</c> structure should be equal to structure,
* used in VCECLB_PrepareEx() function to configure frame grabber.
| Bayer CFA | TRUESENSE Sparse CFA | 
| ----: | :----: | 
| ![Bayer CFA](/grid_bayer.png "Bayer CFA")    | ![TRUESENSE Sparse CFA](/grid_ts.png "TrueSense CFA")     | 
*
* If <c>cameraData</c> specifies RGB input
* (i.e. BitDepth set to 24, 30 or 36 bits), then de-mosaicking algorithm ignored.
*
* If <c>BayerPattern</c> is <c>false</c>, the BayerStart parameter ignored.
*
* The <c>Gain</c> and <c>Offset</c> parameters are used only with RGB input or
* if <c>BayerPattern</c> is <c>true</c>, otherwise they ignored
*
* <c>LookupTableLevels</c> and <c>LookupTableValues</c> should either
* both be NULL or both set. For RGB image, lookup table ignored.
*
* Size of lookup tables buffers should be equal to the number of possible values
* for specified BitDepth. I.e. for 10bit image lookup tables should have
* 1024 entries, for 12bit - 4096 entries, etc.
*

*/
typedef struct tagVCECLB_RawPixelInfoEx
{
	void* _unused0; /**< Reserved for future use. Should be <c>NULL</c> */
	VCECLB_CameraDataEx cameraData; /**< Frame grabber configuration settings */
	unsigned char BayerPattern; /**< Use Bayer or TrueSense Color Filter Array (CFA) de-mosaicking algorithm 
	* - 0 Monochrome
	* - 1 Bayer CFA
	* - 2 TRUESENSE Sparse CFA
	*/
	unsigned char BayerStart; /**< Bayer or TRUESENSE Sparse Color Filter Array start pixel number
				 - For Bayer CFA (see picture below):
					   + 0  GR-BG,  1  RG-GB
					   + 2  BG-GR,  3  GB-RG
				 - For TRUESENSE Sparse CFA (see picture below):
					   + 0  PB-BP,  1  BP-PG,  2  PG-GP,  3  GP-PB
					   + 4  BP-PG,  5  PG-GP,  6  GP-PR,  7  PB-RP
					   + 8  PG-GP,  9  GP-PR,  10 PR-RP,  11 RP-PG
					   + 12 GP-PB,  13 PR-BP,  14 RP-PG,  15 PG-GP
					  */
	signed char RedOffset; /**< Offset value for red component */
	signed char GreenOffset; /**< Offset value for green component */
	signed char BlueOffset; /**< Offset value for blue component */
	double RedGain; /**< Gain value for red component */
	double GreenGain; /**< Gain value for green component */
	double BlueGain; /**< Gain value for blue component */
	int* LookupTableLevels; /**< Optional lookup table levels */
	int* LookupTableValues; /**< Optional lookup table values */
} VCECLB_RawPixelInfoEx;

/// Frame grabber configuration file
/**
* \note
* String buffers should be allocated by application.
* If supplied buffer is too small to hold the requested string,
* the string is truncated and followed by a null character.
*
* Frame grabber configuration settings is provided via <c>pixelInfo.cameraData</c> field
*/
typedef struct tagVCECLB_ConfigurationW {
	wchar_t *	lpszManufacturer; /**< Pointer to the buffer with camera manufacturer string */
	unsigned long	cchManufacturer; /**< Length of the buffer with camera manufacturer in chars */

	wchar_t *	lpszModel; /**< Pointer to the buffer with camera model string */
	unsigned long	cchModel; /**< Length o thef buffer with camera model in chars */

	wchar_t *	lpszDescription; /**< Pointer to the buffer with camera description string */
	unsigned long	cchDescription; /**< Length of the buffer with camera model in chars */

	wchar_t *	lpszAlias; /**< Pointer to the buffer with camera alias string */
	unsigned long	cchAlias; /**< Length of the buffer with camera alias in chars */

	VCECLB_RawPixelInfoEx pixelInfo; /**< Raw pixel description */
	VCECLB_CCStrobesEx strobes; /**< Camera control strobes configuration */
	VCECLB_PulseGeneratorEx pulseGenerator; /**< Pulse generator configuration */
	unsigned long	baudRate; /**< Camera communication baud rate */
} VCECLB_ConfigurationW;

/// Frame grabber configuration file
/**
*\note
* String buffers should be allocated by application.
* If supplied buffer is too small to hold the requested string,
* the string is truncated and followed by a null character.
*
* Frame grabber configuration settings is provided via <c>pixelInfo.cameraData</c> field
*/
typedef struct tagVCECLB_ConfigurationA {
	char *	lpszManufacturer; /**< Pointer to the the buffer with camera manufacturer string */
	unsigned long	cchManufacturer; /**< Length of the buffer with camera manufacturer in chars */

	char *	lpszModel; /**< Pointer to the buffer with camera model string */
	unsigned long	cchModel; /**< Length of the buffer with camera model in chars */

	char *	lpszDescription; /**< Pointer to the buffer with camera description string */
	unsigned long	cchDescription; /**< Length of the buffer with camera model in chars */

	char *	lpszAlias; /**< Pointer to the buffer with camera alias string */
	unsigned long	cchAlias; /**< Length of the buffer with camera alias in chars */

	VCECLB_RawPixelInfoEx pixelInfo; /**< Raw pixel description */
	VCECLB_CCStrobesEx strobes; /**< Camera control strobes configuration */
	VCECLB_PulseGeneratorEx pulseGenerator; /**< Pulse generator configuration */
	unsigned long	baudRate; /**< Camera communication baud rate */
} VCECLB_ConfigurationA;

/// Frame grabber configuration file
	/** \see
	*- VCECLB_ConfigurationW for UNICODE version of structure
	*- VCECLB_ConfigurationA for Multibyte version of structure
	*/
#ifdef UNICODE
#define VCECLB_Configuration VCECLB_ConfigurationW
#else
#define VCECLB_Configuration VCECLB_ConfigurationA
#endif
///@}


/////////////////////////////////////////////////////////
/// \defgroup flex_func FrameLink Express Functions
/// The following functions are used with FrameLink Express
/// @{
/////////////////////////////////////////////////////////

#ifdef __cplusplus
VCECLB_SDK_API bool VCECLB_CALL operator== (const VCECLB_TapConfig& left,const VCECLB_TapConfig& right);
VCECLB_SDK_API bool VCECLB_CALL operator!= (const VCECLB_TapConfig& left,const VCECLB_TapConfig& right);
#endif

#ifdef __cplusplus
extern "C" {
#endif
	/////////////////////////////////////////////////////////
	/// \defgroup flex_func_init FrameLink Express initialization functions
	///@{
	/////////////////////////////////////////////////////////

	/// Initializes FrameLink Express or FrameLink frame grabber
	/** 
	* \return
	* If the function succeeds, the return value is an open handle
	* to the first available frame grabber, \n
	* If the function fails, the return value is NULL. To get
	* extended error information, call VCECLB_CardLastError()
	* \sample
	* \code
	* void * hGrabber = VCECLB_Init(); // Open frame grabber
	* if(hGrabber == NULL) // Frame grabber is not accessible
	*   ... // Handle error
	* // Do other stuff
	* VCECLB_Done(hGrabber); // Close frame frabber
	* \endcode
	*/
	VCECLB_SDK_API void * VCECLB_CALL VCECLB_Init(void);

	/// Closes frame grabber
	/**
	* @param hVCECLB Handle to frame grabber
	*\return
	* The return value is the error code.
	* \sample
	* For sample code see VCECLB_Init() function
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_Done(HANDLE hVCECLB);

	/// Get framegrabber capability
	/**
	* @param hVCECLB Handle to frame grabber
	* @param cap Capability flag
	*\return
	* Function returns VCECLB_Err_Success if grabber supports the capability 
	* and VCECLB_Err_notSupported if capability is not supported
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetCapability(HANDLE hVCECLB, VCECLB_Capability cap);
	///@}

	/// \defgroup flex_func_uart FrameLink Express UART functions
	///@{

	/// Acquires the access to UART operations on specified port
	/**
	* @param hVCECLB Handle to frame grabber
	* @param port Port number
	*\return
	* The return value is the error code.
	*\sample
	*\code
	* void * hGrabber; // Handle to frame grabber
	* char port; // Input port
	* VCECLB_Error err = VCECLB_UART_InitEx(hGrabber, port) // Acquire access to UART
	* if(err != VCECLB_Err_Success) // Port busy.
	*   ... // Handle error
	* // Do other stuff
	* VCECLB_UART_DoneEx(hGrabber, port); // Release access to UART
	*\endcode
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_InitEx(HANDLE hVCECLB, char port);

	/// Releases access to UART operations on port
	/**
	* @param hVCECLB Handle to frame grabber
	* @param port Port number
	*\return
	* The return value is the error code.
	*\sample
	* For an example, see the VCECLB_UART_InitEx() function
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_DoneEx(HANDLE hVCECLB, char port);

	/// Sets the baud rate for UART operations
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param baudRate Baud rate value at which the communications device operates
	*\return
	* The return value is the error code.
	*\sample
	*\code
	* // Set baud rate to 9600 bps
	* VCECLB_UART_SetBREx(hGrabber, port, 9600);
	* \endcode
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_SetBREx(HANDLE hVCECLB, char port, unsigned long baudRate);

	/// Retrieves the value of baud rate for UART operations
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pBaudRate Pointer to the variable that recives the value of
	*		baud rate at which the communications device operates
	*\return
	* The return value is the error code.
	*\sample
	*\code
	* unsigned long baudRate;
	* // Get current baud rate value
	* VCECLB_UART_GetBREx(hGrabber, port, &baudRate);
	*\endcode
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_GetBREx(HANDLE hVCECLB, char port, unsigned long *pBaudRate);

	/// Sets the time-out parameters for all read and write operations on a specified communications port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param lpCommTimeouts Pointer to a COMMTIMEOUTS structure that 
	*			contains the new time-out values.
	*\return
	* The return value is the error code.
	*\note
	* The COMMTIMEOUTS structure declared in Windows API <i>Winbase.h</i>;
	* include <i>Windows.h</i>.\n
	* The parameters determine the behavior of VCECLB_UART_ReadEx() and 
	* VCECLB_UART_WriteEx() operations on the port.
	*\code
	* typedef struct _COMMTIMEOUTS {
	*   DWORD ReadIntervalTimeout;
	*   DWORD ReadTotalTimeoutMultiplier;
	*   DWORD ReadTotalTimeoutConstant;
	*   DWORD WriteTotalTimeoutMultiplier;
	*   DWORD WriteTotalTimeoutConstant;
	* } COMMTIMEOUTS,  *LPCOMMTIMEOUTS;
	*\endcode
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_SetTimeoutsEx(HANDLE hVCECLB, char port, LPCOMMTIMEOUTS lpCommTimeouts);

	/// Retrieves the time-out parameters for all read and write operations on a specified communications port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param lpCommTimeouts Pointer to a COMMTIMEOUTS structure in which 
	*			the time-out information is returned.
	*\return
	* The return value is the error code.
	*\note
	* For more information about time-out values for communications
	* devices, see the VCECLB_UART_SetTimeoutsEx() function.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_GetTimeoutsEx(HANDLE hVCECLB, char port, LPCOMMTIMEOUTS lpCommTimeouts);

	/// Writes the data to the communication port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param buffer Pointer to the buffer containing the data to be written to the port.
	*@param bufferSize Pointer to variable that specifies length of buffer 
	*		and on successful output recieves number of bytes written.
	*@param serialTimeout Maximum time-out value in milliseconds.
	*\return
	* The return value is the error code.
	*\note
	* If <c>serialTimeout</c> set to zero, time-out parameters set by 
	* VCECLB_UART_SetTimeoutsEx() used.
	* Otherwise time-out parameters overrides by <c>serialTimeout</c>.\n
	* If time-out occurs and no data has been written, VCECLB_Err_UART_Timeout returns,
	* otherwise return value is VCECLB_Err_Success.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_WriteEx(HANDLE hVCECLB, char port, unsigned char* buffer, unsigned long* bufferSize, unsigned long serialTimeout);

	/// Reads the data from the communication port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param buffer Pointer to the buffer that receives the data read from the port.
	*@param bufferSize Pointer to variable that specifies length of buffer 
	*		and on successful output recieves number of bytes read.
	*@param serialTimeout Maximum time-out value in milliseconds.
	*\return
	* The return value is the error code.
	*\note
	* If <c>serialTimeout</c> set to zero, time-out parameters set by 
	* VCECLB_UART_SetTimeoutsEx() used.
	* Otherwise time-out parameters overrides by <c>serialTimeout</c>. \n
	* If time-out occurs and no data has been read, VCECLB_Err_UART_Timeout returns, 
	* otherwise return value is VCECLB_Err_Success.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_ReadEx(HANDLE hVCECLB, char port, unsigned char* buffer, unsigned long* bufferSize, unsigned long serialTimeout);

	/// Returns number of bytes available in driver input buffer for the communication port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param numBytes Pointer to variable that receivs number of bytes 
	*		available in driver input buffer.
	*\return
	* The return value is the error code.
	*\note
	* The <c>numBytes</c> bytes can be read from communication port without blocking.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_GetNumBytesAvailEx(HANDLE hVCECLB, char port, unsigned int* numBytes);

	/// Clears driver input buffer for communication port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*\return
	* The return value is the error code.
	*\note
	* This function clears all data sent by camera to frame grabber, 
	* that has not been read yet.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_FlushEx(HANDLE hVCECLB, char port);

	/// Creates virtual COM port and associates it with specified commincation port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param dwPortNumber COM port to create
	*\return
	* The return value is the error code.
	*\note
	* This function creates virtual COM port (like COM1, COM2, etc) and 
	* associates it with specified frame grabber communication port.
	* Virtual COM port may later be used with any terminal application, 
	* or using Windows API functions for Communication Ports.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_CreateSerialPortEx(HANDLE hVCECLB, char port, unsigned long dwPortNumber);

	/// Deletes virtual COM port associated with specified commincation port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*\return
	* The return value is the error code.
	*\note
	* This function removes virtual COM port (like COM1, COM2, etc) that 
	* was previously associated with frame grabber communication port 
	* using VCECLB_UART_CreateSerialPortEx() function.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UART_DeleteSerialPortEx(HANDLE hVCECLB, char port);
	///@}

	/////////////////////////////////////////////////////////
	/// \defgroup flex_func_imaq FrameLink Express Image acquisition functions
	///@{
	/////////////////////////////////////////////////////////

	/// Acquires the access to image acquisition on spcified port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetDMAAccessEx(HANDLE hVCECLB, char port);

	/// Releases access to image acquisition on port.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_ReleaseDMAAccessEx(HANDLE hVCECLB, char port);

	/// Analyzes input signal and returns number of pixels and lines per one tap.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pPixels Pointer to variable to recieve number of pixels per tap
	*@param pLines Pointer to variable to recieve number of lines per tap
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_LearnFrameSizeEx(HANDLE hVCECLB, char port, unsigned long* pPixels, unsigned long *pLines);

	/// Retrieves camera online status
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pCameraOnline Pointer to variable to recieve camera online status.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetCameraStatusEx(HANDLE hVCECLB, char port, unsigned char *pCameraOnline);

	/// Sets length of internal buffer queue, used to acquire data from framegrabber
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param bufferCount New length of buffer queue
	*\return
	* The return value is the error code.
	*\note
	* Length of buffer queue should be greater than or equal to 3
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SetBufferCountEx(HANDLE hVCECLB, char port, unsigned long bufferCount);

	/// Configures frame grabber with specified settings
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pCameraData Pointer to variable that specifies frame grabber parameters
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_PrepareEx(HANDLE hVCECLB, char port, VCECLB_CameraDataEx* pCameraData);

	/// Checks if tap configuration is equal to one of predefined tap configuration
	/**
	*@param config Pointer to variable that specifies tap configuration
	*\return
	* The function returns VCECLB_TapConfig_Custom if tap configuration 
	* not recognized as predefined.\n
	* The function returns one of the VCECLB_TapConfigPredefined 
	* enumeration value, that represents predefined tap configuration
	*/
	VCECLB_SDK_API VCECLB_TapConfigPredefined VCECLB_CALL VCECLB_IsTapConfigPredefined(const VCECLB_TapConfig* config);

	/// Fills VCECLB_TapConfig variable with values for predefined tap configuration
	/**
	*@param config Pointer to variable to recieve tap configuration
	*@param predef Predefined tap configuration value
	*/
	VCECLB_SDK_API void VCECLB_CALL VCECLB_GetPredefinedTapConfig(VCECLB_TapConfigPredefined predef, VCECLB_TapConfig* config);

	/// Starts image acquisition on specified port
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param queueMode 
	* - 0 - Causes oldest frame in queue to be overwritten by new incoming frame, if no free frames available in the queue
	* - 1 - Causes new incoming frames to be dropped, if no available free frames in the queue 
	*@param lpfnCallback Pointer to the application-defined function to 
	*			be executed by the grabbing thread when new image acquired
	*@param lpUserData Points to the application-supplied data. 
	*			The data is passed to the callback function 
	*			along with the image information.
	*\return
	* The return value is the error code.
	*\note
	* See GrabFrame_CallbackEx for more information about callback function.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_StartGrabEx(HANDLE hVCECLB, char port, int queueMode, VCECLB_GrabFrame_CallbackEx lpfnCallback, void* lpUserData);

	/// Stops image acquisition on specified port
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_StopGrabEx(HANDLE hVCECLB, char port);

	/// Retrieves image acquisition statistical information
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pGrabStat Pointer to variable to recieve grabbing statistic.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetGrabStatEx(HANDLE hVCECLB, char port, VCECLB_GrabStatEx* pGrabStat);

	/// Sets time-out value for image acquisition operation.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param timeout Time-out value in milliseconds for image acquisition operation.
	*\return
	* The return value is the error code.
	*\note
	* This function specifies time-out value for VCECLB_SnapEx() function. Default time-out value is 500 milliseconds
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SetDMATimeoutEx(HANDLE hVCECLB, char port, unsigned long timeout);

	/// Snaps images to user specified buffers.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param lpBuffer Pointer to buffer to store acquired images.
	*@param dwBufferSize Size of buffer for images.
	*@param lpTSBuf Pointer to buffer to store timestamp values for acquired images.
	*@param dwTSBufSize Size of buffer for timestamps
	*@param pdwSnappedFrames Pointer to variable to recieve number of snapped frames
	*@param pdwAlignedFrameSize Pointer to variable to recieve length of each frame
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SnapEx(HANDLE hVCECLB, char port, void* lpBuffer, unsigned int dwBufferSize, void* lpTSBuf, unsigned int dwTSBufSize, unsigned int* pdwSnappedFrames, unsigned int* pdwAlignedFrameSize);

	/// Sets user-specified buffers to grab images
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param lplpBuffer Array of pointers to buffers to store acquired images.
	*@param lpBufSizes Array of sizes of buffers
	*@param count Length of array
	*@param pdwAlignedFrameSize Pointer to variable to recieve length of each frame
	*\return
	* The return value is the error code.
	*\note
	* each buffer in array should starts from start of memory page (usualy 4096=0x1000)
	* and should have size at least <c>*pdwAlignedFrameSize</c>
	*/
	VCECLB_Error VCECLB_CALL VCECLB_SetBuffers(HANDLE hVCECLB, char port, void** lplpBuffers, UINT32* lpBufSizes, UINT32 count, UINT32* pdwAlignedFrameSize);

	// Retrives last acquired buffer data
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pFrameInfo pointer to structure to recieve buffer data
	*\return
	* The return value is the error code.
	*/
	VCECLB_Error VCECLB_CALL VCECLB_GetLastBufferData(HANDLE hVCECLB, char port, VCECLB_FrameInfoEx* pFrameInfo);

	/// Stops image acquisition operations
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_ResetGrabberEx(HANDLE hVCECLB, char port);
	///@}


	////////////////////////////////////////////////////
	/// \defgroup flex_func_pg FrameLink Express camera control and pulse generator functions
	///@{
	////////////////////////////////////////////////////

	/// Retrieves camera control strobes states
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pCCStrobes Pointer to variable to recieve camera control strobes states
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetCCStateEx(HANDLE hVCECLB, char port, VCECLB_CCStrobesEx* pCCStrobes);

	/// Sets camera control strobes states
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pCCStrobes Pointer to variable that specifies camera control strobes states
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SetCCStateEx(HANDLE hVCECLB, char port, const VCECLB_CCStrobesEx* pCCStrobes);

	/// Retrieves camera control pulse generator parameters
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pPulseGenerator Pointer to variable to recieve camera control 
	*		pulse generator parameters
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetCCPulseGeneratorEx(HANDLE hVCECLB, char port, VCECLB_PulseGeneratorEx* pPulseGenerator);

	/// Sets camera control pulse generator parameters
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param pPulseGenerator Pointer to variable that specifies camera 
	*		control pulse generator parameters
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SetCCPulseGeneratorEx(HANDLE hVCECLB, char port, const VCECLB_PulseGeneratorEx* pPulseGenerator);

	/// Starts/stops camera control pulse generator
	/**
	*@param hVCECLB Handle to frame grabber
	*@param port Port number
	*@param bStart Specifies whether to start or stop the pulse generator.\n
	*		If this parameter is true, the pulse generator started.\n
	*		If the parameter is false, the pulse generator stoped.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_StartPulseGeneratorEx(HANDLE hVCECLB, char port, unsigned char bStart);
	///@}

	////////////////////////////////////////////////////
	/// \defgroup flex_func_unpack FrameLink Express pixel unpacking and image saving functions
	///@{
	////////////////////////////////////////////////////

	/// Converts raw image data to specified image format
	/**
	*@param pPixelInfo Pointer to variable that specifies raw data format
	*@param pRawPixelsC Pointer to buffer with raw data
	*@param pPixels Pointer to buffer to recieve unpacked image
	*@param pStrideSize Pointer to variable that specifies or recieves 
	*		unpacked image stride size
	*@param OutputFormat Unpacked image format options.\n
	*		This parameter may include combination of next values:\n
	*		Output bit depth:
	*		\table{Value,Meaning}
	*		\row{VCECLB_EX_FMT_8BIT, Produce 8bit output}
	*		\row{VCECLB_EX_FMT_16BIT, Produce 16bit output\, if input is not 8bit}
	*		\row{VCECLB_EX_FMT_16BIT_NORMALIZE, Produce 16bit normalized output\, if input is not 8bit}
	*		\endtable
	*		Output channels, for RGB or Bayer images
	*		\table{Value,Meaning}
	*		\row{VCECLB_EX_FMT_3Channel, Produce 3 channels output (24bit or 48bit\, depending on input and output)}
	*		\row{VCECLB_EX_FMT_4Channel, Produce 4 channels output (32bit or 64bit\, depending on input and output)}
	*		\endtable
	*		Output image direction
	*		\table{Value,Meaning}
	*		\row{VCECLB_EX_FMT_TopDown, Produce top-down direction image}
	*		\row{VCECLB_EX_FMT_BottomUp, Produce bottom-up direction image}
	*		\endtable
	*@param pOutputBitDepth Pointer to variable to recieve information 
	*		about unpacked image bit depth
	*\return
	* The return value is the error code.
	*\note
	* Next rule applied to <c>OutputFormat</c> parameter:
	* <c>VCECLB_EX_FMT_8BIT</c>, <c>VCECLB_EX_FMT_16BIT</c> and 
	* <c>VCECLB_EX_FMT_16BIT_NORMALIZE</c> are mutual exclusive. \n
	* In case of 8bit or 24bit input <c>VCECLB_EX_FMT_16BIT</c> and 
	* <c>VCECLB_EX_FMT_16BIT_NORMALIZE</c> ignored. \n
	* <c>VCECLB_EX_FMT_3Channel</c> and <c>VCECLB_EX_FMT_4Channel</c> are mutual exclusive.\n
	* In case of monochrome input (not RGB24, RGB30, or RGB36 and not bayer pattern) 
	* <c>VCECLB_EX_FMT_3Channel</c> and <c>VCECLB_EX_FMT_4Channel</c> ignored. \n
    * <c>VCECLB_EX_FMT_TopDown</c> and <c>VCECLB_EX_FMT_BottomUp</c> are mutual exclusive.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_UnpackRawPixelsEx(const VCECLB_RawPixelInfoEx *pPixelInfo, const void *pRawPixelsC, void *pPixels, INT_PTR *pStrideSize, unsigned char OutputFormat, unsigned long* pOutputBitDepth);

	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetFromGrabQueue(HANDLE hVCECLB, char port,unsigned long TimeOut,void* pBuf, unsigned int* pdwBufferSize,unsigned int* pQueueLen);

#ifndef DOXYGEN_SHOULD_SEE_THIS

///Output bit depth
#define VCECLB_EX_FMT_8BIT 0 /**< Produce 8bit output */
#define VCECLB_EX_FMT_16BIT 1 /**< Produce 16bit output, if input is not 8bit */
#define VCECLB_EX_FMT_16BIT_NORMALIZE 3 /**< Produce 16bit normalized output, if input is not 8bit */

/// Output channels, for RGB or Bayer images 
#define VCECLB_EX_FMT_3Channel 0 /**< produce 3 channels output (24bit or 48bit, depending on input and output) */
#define VCECLB_EX_FMT_4Channel 4  /**< produce 4 channels output (32bit or 64bit, depending on input and output) */

/// Output image direction
#define VCECLB_EX_FMT_TopDown 0 /**< Produce top-down direction image */
#define VCECLB_EX_FMT_BottomUp 8 /**< Produce bottom-up direction image */

#endif

	/// Saves raw data to bitmap file
	/**
	*@param pPixelInfo Pointer to variable that specifies raw data format
	*@param pRawPixelsC Pointer to buffer with raw data
	*@param hFile Handle to file opened with CreateFile Windows API function
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SaveRawToBMPFileHandle(const VCECLB_RawPixelInfoEx *pPixelInfo, const void *pRawPixelsC, void * hFile);

	/// Saves raw data to bitmap file
	/**
	*@param pPixelInfo Pointer to variable that specifies raw data format
	*@param pRawPixelsC Pointer to buffer with raw data
	*@param lpszFileName A pointer to a null-terminated string that 
	*			specifies the name of an file to create.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SaveRawToBMPFileA(const VCECLB_RawPixelInfoEx *pPixelInfo, const void *pRawPixelsC, const char* lpszFileName);

	/// Saves raw data to bitmap file
	/**
	*@param pPixelInfo Pointer to variable that specifies raw data format
	*@param pRawPixelsC Pointer to buffer with raw data
	*@param lpszFileName A pointer to a null-terminated string that 
	*			specifies the name of an file to create.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SaveRawToBMPFileW(const VCECLB_RawPixelInfoEx *pPixelInfo, const void *pRawPixelsC, const wchar_t* lpszFileName);

	/// Saves raw data to bitmap file
	/** \see
	*- VCECLB_SaveRawToBMPFileW for UNICODE version of function
	*- VCECLB_SaveRawToBMPFileA for Multibyte version of fuction
	*/
#ifdef UNICODE
#define VCECLB_SaveRawToBMPFile  VCECLB_SaveRawToBMPFileW 
#else
#define VCECLB_SaveRawToBMPFile  VCECLB_SaveRawToBMPFileA 
#endif

	/// Saves raw data to JPEG file
	/**
	*@param pPixelInfo Pointer to variable that specifies raw data format
	*@param pRawPixelsC Pointer to buffer with raw data
	*@param lpszFileName A pointer to a null-terminated string that specifies the name of an file to create.
	*@param nQuality JPEG compression quality (1-100)
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SaveRawToJPGFileA(const VCECLB_RawPixelInfoEx *pPixelInfo, const void *pRawPixelsC, const char* lpszFileName, unsigned char nQuality);

	/// Saves raw data to JPEG file
	/**
	*@param pPixelInfo Pointer to variable that specifies raw data format
	*@param pRawPixelsC Pointer to buffer with raw data
	*@param lpszFileName A pointer to a null-terminated string that specifies the name of an file to create.
	*@param nQuality JPEG compression quality (1-100)
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SaveRawToJPGFileW(const VCECLB_RawPixelInfoEx *pPixelInfo, const void *pRawPixelsC, const wchar_t* lpszFileName, unsigned char nQuality);

	/// Saves raw data to JPEG file
	/** \see
	*- VCECLB_SaveRawToJPGFileW for UNICODE version of function
	*- VCECLB_SaveRawToJPGFileA for Multibyte version of fuction
	*/
#ifdef UNICODE
#define VCECLB_SaveRawToJPGFile  VCECLB_SaveRawToJPGFileW
#else
#define VCECLB_SaveRawToJPGFile  VCECLB_SaveRawToJPGFileA
#endif

	/// Saves raw data to TIFF file
	/**
	*@param pPixelInfo Pointer to variable that specifies raw data format
	*@param pRawPixelsC Pointer to buffer with raw data
	*@param lpszFileName A pointer to a null-terminated string that specifies the name of an file to create.
	*@param OutputFormat Unpacked image format options
	*\return
	* The return value is the error code.
	*\note
	* For <c>OutputFormat</c> values see VCECLB_UnpackRawPixelsEx() function
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SaveRawToTIFFFileA(const VCECLB_RawPixelInfoEx *pPixelInfo, const void *pRawPixelsC, const char* lpszFileName, unsigned char OutputFormat);

	/// Saves raw data to TIFF file
	/**
	*@param pPixelInfo Pointer to variable that specifies raw data format
	*@param pRawPixelsC Pointer to buffer with raw data
	*@param lpszFileName A pointer to a null-terminated string that specifies the name of an file to create.
	*@param OutputFormat Unpacked image format options
	*\return
	* The return value is the error code.
	*\note
	* For <c>OutputFormat</c> values see VCECLB_UnpackRawPixelsEx() function
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SaveRawToTIFFFileW(const VCECLB_RawPixelInfoEx *pPixelInfo, const void *pRawPixelsC, const wchar_t* lpszFileName, unsigned char OutputFormat);

	/// Saves raw data to TIFF file
	/** \see
	*- VCECLB_SaveRawToTIFFFileW for UNICODE version of function
	*- VCECLB_SaveRawToTIFFFileA for Multibyte version of fuction
	*/
#ifdef UNICODE	
#define VCECLB_SaveRawToTIFFFile VCECLB_SaveRawToTIFFFileW 
#else
#define VCECLB_SaveRawToTIFFFile VCECLB_SaveRawToTIFFFileA
#endif

	/// Convers raw data to DIB
	/**
	*@param pPixelInfo Pointer to variable that specifies raw data format
	*@param pRawPixelsC Pointer to buffer with raw data
	*@param phDIB Pointer to handle to recieve handle to DIB
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_ConvertPixels2DIBEx(const VCECLB_RawPixelInfoEx *pPixelInfo, const void *pRawPixelsC, void ** phDIB);

	/// Draws DIB to specified Device Context
	/**
	*@param hdc Handle to device context
	*@param hdib Handle to DIB
	*@param xPos x-coord of destination upper-left corner
	*@param yPos y-coord of destination upper-left corner
	*@param xSize width of destination rectangle
	*@param ySize height of destination rectangle
	*\return
	* The return value is the error code.
	*\note
	* If xSize and ySize set to zero - original size used.\n
	* If destination size is equal to original, SetDIBitsToDevice Windows API function used, 
	*  otherwise StretchDIBits Windows API function used.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_DrawDIB (HDC hdc, HGLOBAL hdib,WORD xPos, WORD yPos, WORD xSize, WORD ySize);

	/// Creates a copy of DIB
	/**
	*@param hDIB Original DIB handle
	*@param phDIB Pointer to handle to recieve handle to DIB 
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_CopyDIB(HGLOBAL hDIB, HGLOBAL *phDIB);

	/// Releases memory used by DIB handle
	/**
	*@param hVCECLB Handle to FrameGrabber. Optional, may be NULL.
	*@param phDIB Pointer to DIB handle.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_ReleaseDIB(HANDLE hVCECLB,HGLOBAL *phDIB);
	///@}


	/// \defgroup flex_func_misc FrameLink Express miscellaneous functions
	///@{

	/// Retrieves last error code.
	/**
	*\return
	* The return value is the error code of last operation.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_CardLastError(void);

	/// Retrieves last system error code.
	/**
	*\return
	* The return value is the system error code of last operation driver operation.
	*/
	VCECLB_SDK_API unsigned long VCECLB_CALL VCECLB_SystemLastError(void);

	/// Retrieves last driver error code.
	/**
	*\return
	* The return value is the driver error code of last operation driver operation.
	*/
	VCECLB_SDK_API unsigned long VCECLB_CALL VCECLB_DriverLastError(void);

	/// Retrieves version information from library, driver and frame grabber.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param pdwLibVerHi Pointer to variable to recieve Major and Middle version numbers of library
	*@param pdwLibVerLo Pointer to variable to recieve Minor and Build version numbers of library
	*@param pdwDrvVerHi Pointer to variable to recieve Major and Middle version numbers of driver
	*@param pdwDrvVerLo Pointer to variable to recieve Minor and Build version numbers of driver
	*@param pdwFirmVer Pointer to variable to recieve version numbers of frame grabber
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetVersions(HANDLE hVCECLB,unsigned long* pdwLibVerHi,unsigned long* pdwLibVerLo, unsigned long* pdwDrvVerHi,unsigned long* pdwDrvVerLo, unsigned long* pdwFirmVer);

	/// Retrieves version information from library, driver and frame grabber.
	/**
	*@param hVCECLB Handle to frame grabber
	*@param pdwImageID Pointer to variable to recieve frame grabber image identificator
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetFPGAImageIDEx(HANDLE hVCECLB, unsigned long* pdwImageID);

	/// Retrieves information about PCI Express bus
	/**
	*@param hVCECLB Handle to frame grabber
	*@param pLinkWidth Pointer to variable to recieve PCI Express link width
	*@param pLinkSpeed Pointer to variable to recieve PCI Express link speed
	*@param pMaxPayloadSizeSupported Pointer to variable to recieve PCI Express Max Payload Size Supported
	*@param pMaxPayloadSize Pointer to variable to recieve PCI Express Max Payload Size
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetPCIExpressBusInfo(HANDLE hVCECLB, unsigned long* pLinkWidth, unsigned long* pLinkSpeed, unsigned long* pMaxPayloadSizeSupported, unsigned long* pMaxPayloadSize);



	///@}



	/// \defgroup flex_func_enum FrameLink Express device enumeration functions
	///@{

	/// Starts enumerating of installed frame grabbers.
	/**
	*\return
	* The return value is the handle to enumerator.
	*\note
	* After the search enumerator is established, use the VCECLB_EnumNext() enumerate the frame grabbers.\n
	* When enumerator handle is not needed, close it by using VCECLB_EnumClose() function
	*\sample
	*\code
	* // Initilize frame grabber description structure
	* VCECLB_EnumData enumData;
	* enumData.cbSize = sizeof(VCECLB_EnumData);
	*
	* // Open enumerator handle
	* void * hDevEnum = VCECLB_EnumInit();
	*
	* //Enumerate through device
	* while(VCECLB_EnumNext(hDevEnum, &enumData) == VCECLB_Err_Success)
	* {
	*   void * hDevice = VCECLB_InitByHandle(enumData.pDeviceData, 0);
	*	 // Do other stuff
	* }
	*
	* // Close enumerator
	* VCECLB_EnumClose(hDevEnum);
	*\endcode
	*/
	VCECLB_SDK_API HANDLE VCECLB_CALL VCECLB_EnumInit(void);

	/// Closes enumerator handle previosly opened by VCECLB_EnumInit() function.
	/**
	*@param hDevEnum Handle to enumerator
	*\return
	* The return value is the error code.
	*\sample
	* See VCECLB_EnumInit() for usage example.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_EnumClose(HANDLE hDevEnum);

	/// Returns next frame grabber information description.
	/**
	*@param hDevEnum Handle to enumerator
	*@param pEnumData Pointer to variable to recieve enumeration data
	*\return
	* VCECLB_Err_Success, if the function succeeds or 
	* VCECLB_Err_noDevicePresent if no more device present.
	*\sample
	* See VCECLB_EnumInit() for usage example.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_EnumNext(void * hDevEnum, VCECLB_EnumData* pEnumData);

	/// Returns number of frame grabbers detected by device enumerator.
	/**
	*@param hDevEnum Handle to enumerator
	*\return
	* Returns number of devices detected
	*/
	VCECLB_SDK_API int VCECLB_CALL VCECLB_EnumSize(void * hDevEnum);

	/// Initializes FrameLink Express or FrameLink frame grabber using specified device descrition.
	/**
	*@param pDeviceData Initialized device data
	*@param bSkipCheck Flag to skip the automatic device add/removal event check.
	*- Set FALSE to enable the automatic device add/removal event check
	*- Set TRUE to skip the automatic device add/removal event check
	* \return
	* If the function succeeds, the return value is an open handle
	* to the first available frame grabber, \n
	* If the function fails, the return value is NULL. To get
	* extended error information, call VCECLB_CardLastError()
	*\sample
	* See VCECLB_EnumInit() for usage example.
	*/
	VCECLB_SDK_API void * VCECLB_CALL VCECLB_InitByHandle(VCECLB_DeviceData* pDeviceData, int bSkipCheck);

	/// Saves device alias in system registry using device data structure
	/**
	*@param pDeviceData Initialized device data
	*@param strDeviceAlias String to be saved in system registry or NULL to delete alias
	*@param global Flag to specify where to store card alias. In case of 'true' System Administrator (priveleged) access required
	*\return
	* VCECLB_Err_Success, if the function succeeds
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SetDeviceAliasA(VCECLB_DeviceData* pDeviceData, LPCSTR strDeviceAlias, bool global);

	/// Saves device alias in system registry using device data structure
	/**
	*@param pDeviceData Initialized device data
	*@param strDeviceAlias String to be saved in system registry or NULL to delete alias
	*@param global Flag to specify where to store card alias. In case of 'true' System Administrator (priveleged) access required
	*\return
	* VCECLB_Err_Success, if the function succeeds
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SetDeviceAliasW(VCECLB_DeviceData* pDeviceData, LPCWSTR strDeviceAlias, bool global);

#ifdef UNICODE
#define VCECLB_SetDeviceAlias VCECLB_SetDeviceAliasW
#else
#define VCECLB_SetDeviceAlias VCECLB_SetDeviceAliasA
#endif

	/// Saves device alias in system registry using device handle
	/**
	*@param hVCECLB Handle to open framegrabber
	*@param strDeviceAlias String to be saved in system registry or NULL to delete alias
	*@param global Flag to specify where to store card alias. In case of 'true' System Administrator (priveleged) access required
	*\return
	* VCECLB_Err_Success, if the function succeeds
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SetDeviceAlias2A(HANDLE hVCECLB, LPCSTR strDeviceAlias, bool global);

	/// Saves device alias in system registry using device handle
	/**
	*@param hVCECLB Handle to open framegrabber
	*@param strDeviceAlias String to be saved in system registry or NULL to delete alias
	*@param global Flag to specify where to store card alias. In case of 'true' System Administrator (priveleged) access required
	*\return
	* VCECLB_Err_Success, if the function succeeds
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SetDeviceAlias2W(HANDLE hVCECLB, LPCWSTR strDeviceAlias, bool global);

#ifdef UNICODE
#define VCECLB_SetDeviceAlias2 VCECLB_SetDeviceAlias2W
#else
#define VCECLB_SetDeviceAlias2 VCECLB_SetDeviceAlias2A
#endif

	/// Retrieves device alias from system registry by device data structure
	/**
	*@param pDeviceData Initialized device data
	*@param strDeviceData Pointer to buffer for returned device alias
	*@param pLen Pointer to variable that specifies length of buffer in chars
	*		and on successful output recieves number of chars returned.
	*		Includes the terminating null character.
	*\return
	* VCECLB_Err_Success, if the function succeeds
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetDeviceAliasA(VCECLB_DeviceData* pDeviceData, LPSTR strDeviceAlias, DWORD* pLen);

	/// Retrieves device alias from system registry by device data structure
	/**
	*@param pDeviceData Initialized device data
	*@param strDeviceData Pointer to buffer for returned device alias
	*@param pLen Pointer to variable that specifies length of buffer in chars
	*		and on successful output recieves number of chars returned.
	*		Includes the terminating null character.
	*\return
	* VCECLB_Err_Success, if the function succeeds
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetDeviceAliasW(VCECLB_DeviceData* pDeviceData, LPWSTR strDeviceAlias, DWORD* pLen);

#ifdef UNICODE
#define VCECLB_GetDeviceAlias VCECLB_GetDeviceAliasW
#else
#define VCECLB_GetDeviceAlias VCECLB_GetDeviceAliasA
#endif

	/// Retrieves device alias from system registry by device handle
	/**
	*@param hVCECLB Handle to open framegrabber
	*@param strDeviceData Pointer to buffer for returned device alias
	*@param pLen Pointer to variable that specifies length of buffer in chars
	*		and on successful output recieves number of chars returned.
	*		Includes the terminating null character.
	*\return
	* VCECLB_Err_Success, if the function succeeds
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetDeviceAlias2A(HANDLE hVCECLB, LPSTR strDeviceAlias, DWORD* pLen);

	/// Retrieves device alias from system registry by device handle
	/**
	*@param hVCECLB Handle to open framegrabber
	*@param strDeviceData Pointer to buffer for returned device alias
	*@param pLen Pointer to variable that specifies length of buffer in chars
	*		and on successful output recieves number of chars returned.
	*		Includes the terminating null character.
	*\return
	* VCECLB_Err_Success, if the function succeeds
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_GetDeviceAlias2W(HANDLE hVCECLB, LPWSTR strDeviceAlias, DWORD* pLen);

#ifdef UNICODE
#define VCECLB_GetDeviceAlias2 VCECLB_GetDeviceAlias2W
#else
#define VCECLB_GetDeviceAlias2 VCECLB_GetDeviceAlias2A
#endif

	/// Returns frame grabber type identificator by handle to frame grabber or by device description, acquired by VCECLB_EnumNext() function.
	/**
	*@param pDeviceData Device description
	*\return
	* Frame grabber type identificator.
	*/
	VCECLB_SDK_API VCECLB_DeviceType VCECLB_CALL VCECLB_GetDeviceTypeEx(VCECLB_DeviceData* pDeviceData);
	
	/// Returns frame grabber type identificator by handle to frame grabber or by device description, acquired by VCECLB_EnumNext() function.
	/**
	*@param hVCECLB Handle to frame grabber
	*\return
	* Frame grabber type identificator.
	*/
	VCECLB_SDK_API VCECLB_DeviceType VCECLB_CALL VCECLB_GetDeviceType2Ex(HANDLE hVCECLB);

	/// Loads configuration from specified FrameLink or FrameLink Express camera file
	/**
	*@param fileName Path to configuration file to load.
	*@param pConfig Pointer to variable to recieve configuration information.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_LoadConfigW(const wchar_t * fileName, VCECLB_ConfigurationW* pConfig);
	
	/// Loads configuration from specified FrameLink or FrameLink Express camera file
	/**
	*@param fileName Path to configuration file to load.
	*@param pConfig Pointer to variable to recieve configuration information.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_LoadConfigA(const char * fileName, VCECLB_ConfigurationA* pConfig);

	/// Loads configuration from specified FrameLink or FrameLink Express camera file
	/** \see
	*- VCECLB_LoadConfigW for UNICODE version of function
	*- VCECLB_LoadConfigA for Multibyte version of fuction
	*/
#ifdef UNICODE
#define VCECLB_LoadConfig VCECLB_LoadConfigW
#else
#define VCECLB_LoadConfig VCECLB_LoadConfigA
#endif

	/// Saves configuration to specified FrameLink Express camera file
	/**
	*@param fileName Path to configuration file to load.
	*@param pConfig Pointer to variable that specifies configuration information.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SaveConfigW(const wchar_t * fileName, VCECLB_ConfigurationW* pConfig);

	/// Saves configuration to specified FrameLink Express camera file
	/**
	*@param fileName Path to configuration file to load.
	*@param pConfig Pointer to variable that specifies configuration information.
	*\return
	* The return value is the error code.
	*/
	VCECLB_SDK_API VCECLB_Error VCECLB_CALL VCECLB_SaveConfigA(const char * fileName, VCECLB_ConfigurationA* pConfig);

	/// Saves configuration to specified FrameLink Express camera file
	/** \see
	*- VCECLB_SaveConfigW for UNICODE version of function
	*- VCECLB_SaveConfigA for Multibyte version of fuction
	*/
#ifdef UNICODE
#define VCECLB_SaveConfig VCECLB_SaveConfigW
#else
#define VCECLB_SaveConfig VCECLB_SaveConfigA
#endif // !UNICODE

	///@}
#ifdef __cplusplus
}
#endif

// Restore previous aligment
#pragma pack(pop)
#endif // VCECLB_H
///@}
///@}
///@}
