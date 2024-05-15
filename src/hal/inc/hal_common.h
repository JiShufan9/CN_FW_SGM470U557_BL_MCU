/* ***************************************************************************** 
;        Program    :   
;        chip       :   
;        Version    :   1.00.00
;        Author     :   
;        Description:    
;    
 ******************************************************************************/ 
#ifndef HAL_COMMON_H
#define HAL_COMMON_H

#include <stdint.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "packs/ATSAMC21N17A_DFP/atsamc21n17a.h"

/*------------------------------------------------------------------------------
Function Enable/Disable Define
*/
#define NVIC_PRIORITY_HIGH          (0x00U)
#define NVIC_PRIORITY_MEDIUM        (0x01U)
#define NVIC_PRIORITY_LOWER         (0x02U)
#define NVIC_PRIORITY_LOWEST        (0x03U)
#define MAX_NVIC_PRIORITY           (0x04U)
/*------------------------------------------------------------------------------
Function Enable/Disable Define
*/
#define FUNC_DISABLE                (0x00U)
#define FUNC_ENABLE                 (0x01U)
/*------------------------------------------------------------------------------
Return Status Define(don't use bit0 for error define)
*/
#define DRIVER_FALSE                (0x00U)
#define DRIVER_TRUE                 (0x01U)
#define DRIVER_TIMEOUT              (0x02U)
#define DRIVER_PARAMETER_ERROR      (0x04U)
#define DRIVER_WRITE_ERROR          (0x06U)
#define DRIVER_REGISTER_ERROR       (0x08U)

#endif