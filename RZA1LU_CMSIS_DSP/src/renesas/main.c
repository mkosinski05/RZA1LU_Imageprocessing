/*******************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only
 * intended for use with Renesas products. No other uses are authorized. This
 * software is owned by Renesas Electronics Corporation and is protected under
 * all applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
 * LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
 * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
 * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
 * ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
 * BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software
 * and to discontinue the availability of this software. By using this software,
 * you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 * Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
 *******************************************************************************/
/*******************************************************************************
 * File Name    : main.c
 * Device(s)    : RZ/A1LU
 * Tool-Chain   : GCC for Renesas RZ
 * OS           : FreeRTOS Version See src/freertos/include/FreeRTOS.h
 * H/W Platform : Stream it! v2 board
 * Description  : WebEngine
 *                This demonstration run on the Renesas Stream it! v2 platform.
 *******************************************************************************/

/* Dependencies */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "arm_math.h"

#include "compiler_settings.h"

#include "iodefine_cfg.h"
#include "control.h"
#include "version.h"
#include "dma_if.h"

#include "spibsc_iobitmask.h"
#include "cpg_iobitmask.h"
#include "gpio_iobitmask.h"

/* STDIO devlink driver drivers */
#include "r_led_drv_api.h"
/* End of STDIO devlink driver drivers */

#include "command.h"
#include "r_task_priority.h"

#include "lwipStart.h"
#include "cmd_tcp_shell.h"
#include "webif.h"
#include "main.h"

#include "test_data.h"
#include "cycle.h"

static st_iostr_t gs_iostr[3];

static int_t g_led_handle = ( -1);

extern int_t gui_main(void);

#if R_SELF_BLINK_TASK_CREATION
/***********************************************************************************************************************
 * Function Name: blink_task
 * Description  : LED blinking task
 * Arguments    : void *parameters
 * Return Value : none
 ***********************************************************************************************************************/
static void blink_task (void *parameters)
{
    UNUSED_PARAM(parameters);
    uint16_t led = LED0;

    if (g_led_handle < 0)
    {
        printf("gs_stdio_led_handle led driver failed to OPEN \r\n");
    }

    /* Endless loop */
    while (1)
    {

        control(g_led_handle, CTL_SET_LED_ON, &led);
        R_OS_TaskSleep(300);

        control(g_led_handle, CTL_SET_LED_OFF, &led);
        R_OS_TaskSleep(700);
    }
}
/***********************************************************************************************************************
 End of function blink_task
 ***********************************************************************************************************************/
#endif

/***********************************************************************************************************************
 * Function Name: console_task
 * Description  : Serial console task, connect 115200:8:N:1
 * Arguments    : void *parameters
 * Return Value : none
 ***********************************************************************************************************************/
static void console_task (void *parameters)
{
    (void) parameters;
    static bool_t isrunning = true;

    R_OS_TaskUsesFloatingPoint();

	// Inialize Drivers and Driver Tasks Here


	// Start Tes Guiliani
    gui_main();



}
static void cmsisdsp_test_task (void *parameters) {

    arm_lms_norm_instance_f32               S7_F32;
    float32_t                               pStateF32[NUMBER_OF_SAMPLES_MAX * 8];
    float32_t   							Dst_f32[MAX_BLOCK_SIZE * 4];
    float32_t                               mu = 0.15f;
    float32_t                               Err_f32[NUMBER_OF_SAMPLES_MAX * 8];
    int32_t     							number_of_samples_max = 256;
    uint16_t 								numTaps = 46;
    uint32_t    cycle, performance[6]={0};

    printf ( "RZa1LU SDK CMISIS Test \n");
    printf ( "CMSIS DSP Normalized LMS\n ");
    memset(pStateF32, 0, sizeof(pStateF32));

    pmon_initial_cycle_counter();
    arm_lms_norm_init_f32(&S7_F32, numTaps, SrcF32_RA, pStateF32, mu, number_of_samples_max);
    while (1) {
    	// Loop through to enable Cacheb
    	for ( int i = 0; i < 10; i++ ) {
			pmon_start_cycle_counter();
			arm_lms_norm_f32(&S7_F32, SrcF32_RB, Sin5kHz_f32, Dst_f32, Err_f32, number_of_samples_max);
			cycle = pmon_read_cycle_counter();
			pmon_read_pmc_counter((void*)performance);
    	}
    	printf ("Number of Cycles			: %d\n",cycle);
    	// Performace monitor Events
    	printf ("PMU Event0 Software Incr		: %d\n", performance[0]); // 0x00	Software increment
    	printf ("PMU Event1 Data Cache miss		: %d\n", performance[1]); // 0x03 Data cache miss
    	printf ("PMU Event2 Inst. No dispatch	: %d\n", performance[2]); // 0x66 Issue does not dispatch any instruction.
    	printf ("PMU Event3 Issue empty			: %d\n", performance[3]); // 0x67 Issue is empty.
    	printf ("PMU Event4 FPU instr			: %d\n", performance[4]); // 0x73 Floating-point instructions.
    	printf ("PMU Event5 Neon Instr			: %d\n", performance[5]); // 0x74 NEON™ instructions.
    	printf ("\n");

    	vTaskDelay( pdMS_TO_TICKS(1000) );

    }

}
/***********************************************************************************************************************
 * Function Name: main
 * Description  : Main entry point
 * Arguments    : none
 * Return Value : 0
 ***********************************************************************************************************************/
int_t main (void)
{
    /* OS variables */
    os_task_t *p_os_task;

    /* open LED driver */
    g_led_handle = open( DEVICE_INDENTIFIER "led", O_RDWR);

#if R_SELF_BLINK_TASK_CREATION
    /* Create a task to blink the LED */
    p_os_task = R_OS_CreateTask("Blink", blink_task, NULL, R_OS_ABSTRACTION_PRV_DEFAULT_STACK_SIZE, TASK_BLINK_TASK_PRI);

    /* NULL signifies that no task was created by R_OS_CreateTask */
    if (NULL == p_os_task)
    {
        /* Debug message */
    }
#endif

    /* Need to determine system state is running */
    if (R_OS_GetNumberOfTasks())
    {
        /* At least 1 task is running so scheduler is up */
        /* As an enhancement we should use a status semaphore to determine if the console wished to terminate the application
         * but for now just assume that the console will never stop */

#if 0
        p_os_task = R_OS_CreateTask("Console", console_task, NULL, R_OS_ABSTRACTION_PRV_HUGE_STACK_SIZE,
                TASK_CONSOLE_TASK_PRI);
#endif
        /* Create a task to run the console */
		p_os_task = R_OS_CreateTask("cmsis tests", cmsisdsp_test_task, NULL, R_OS_ABSTRACTION_PRV_HUGE_STACK_SIZE,
				TASK_CONSOLE_TASK_PRI);
        /* NULL signifies that no task was created by R_OS_CreateTask */
        if (NULL == p_os_task)
        {
            /* Debug message */
            /* R_COMPILER_Nop() */
            ;
        }

        while (1)
        {
            R_OS_TaskSleep(10000);
        }
    }

    /* Shut down all system resources */
    if (( -1) != g_led_handle)
    {
        close(g_led_handle);
    }

    /* This function should never return */
    while (1)
    {
        /* R_COMPILER_Nop() */
        ;
    }

    return 0;
}
/***********************************************************************************************************************
 End of function main
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: abort
 * Description  : abort handler may be called by libraries
 * Arguments    : none
 * Return Value : 0
 ***********************************************************************************************************************/
void abort (void)
{
    while (1)
    {
        R_COMPILER_Nop();
    }
}
/***********************************************************************************************************************
 End of function abort
 ***********************************************************************************************************************/
