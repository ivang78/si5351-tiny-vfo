/**
 * Microsoft Sans font 16X32
 * SSD1306xLED - Library for the SSD1306 based OLED/PLED 128x64 displays
 */

// ----------------------------------------------------------------------------

#include <avr/pgmspace.h>

// ----------------------------------------------------------------------------

/* Microsoft Sans 16x32 font */
const uint8_t ssd1306xled_font16x32data [] PROGMEM = {
	/* @0 ',' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0xC7, 0x00, 0x00, 0x00, // ##   ###                    
	0xFF, 0x00, 0x00, 0x00, // ########                    
	0x3F, 0x00, 0x00, 0x00, //   ######                    
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             

	/* @64 '-' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x0E, 0x00, 0x00, //             ###             
	0x00, 0x0E, 0x00, 0x00, //             ###             
	0x00, 0x0E, 0x00, 0x00, //             ###             
	0x00, 0x0E, 0x00, 0x00, //             ###             
	0x00, 0x0E, 0x00, 0x00, //             ###             
	0x00, 0x0E, 0x00, 0x00, //             ###             
	0x00, 0x0E, 0x00, 0x00, //             ###             
	0x00, 0x0E, 0x00, 0x00, //             ###             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             

	/* @128 '.' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x07, 0x00, 0x00, 0x00, //      ###                    
	0x07, 0x00, 0x00, 0x00, //      ###                    
	0x07, 0x00, 0x00, 0x00, //      ###                    
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             

	/* @192 '/' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x06, 0x00, 0x00, 0x00, //      ##                     
	0x07, 0xC0, 0x00, 0x00, //      #####                  
	0x03, 0xF8, 0x00, 0x00, //       #######               
	0x00, 0x3F, 0x80, 0x00, //           #######           
	0x00, 0x07, 0xF0, 0x00, //              #######        
	0x00, 0x00, 0xFE, 0x00, //                 #######     
	0x00, 0x00, 0x0F, 0xE0, //                     ####### 
	0x00, 0x00, 0x01, 0xF0, //                        #####
	0x00, 0x00, 0x00, 0x30, //                           ##
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             

	/* @256 '0' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x1F, 0xFC, 0x00, //            ###########      
	0x00, 0x7F, 0xFF, 0x00, //          ###############    
	0x01, 0xFF, 0xFF, 0xC0, //        ###################  
	0x03, 0xE0, 0x03, 0xE0, //       #####           ##### 
	0x03, 0x80, 0x00, 0xE0, //       ###               ### 
	0x07, 0x00, 0x00, 0x70, //      ###                 ###
	0x06, 0x00, 0x00, 0x30, //      ##                   ##
	0x06, 0x00, 0x00, 0x30, //      ##                   ##
	0x06, 0x00, 0x00, 0x30, //      ##                   ##
	0x07, 0x00, 0x00, 0x70, //      ###                 ###
	0x03, 0x80, 0x00, 0xE0, //       ###               ### 
	0x03, 0xE0, 0x03, 0xE0, //       #####           ##### 
	0x01, 0xFF, 0xFF, 0xC0, //        ###################  
	0x00, 0x7F, 0xFF, 0x00, //          ###############    
	0x00, 0x1F, 0xFC, 0x00, //            ###########      

	/* @320 '1' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x03, 0x00, //                       ##    
	0x00, 0x00, 0x03, 0x00, //                       ##    
	0x00, 0x00, 0x03, 0x00, //                       ##    
	0x00, 0x00, 0x03, 0x80, //                       ###   
	0x00, 0x00, 0x01, 0xC0, //                        ###  
	0x07, 0xFF, 0xFF, 0xE0, //      ###################### 
	0x07, 0xFF, 0xFF, 0xF0, //      #######################
	0x07, 0xFF, 0xFF, 0xF0, //      #######################
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             

	/* @384 '2' (16 pixels wide) */
	0x06, 0x00, 0x00, 0x00, //      ##                     
	0x07, 0x80, 0x06, 0x00, //      ####            ##     
	0x07, 0xC0, 0x07, 0x80, //      #####           ####   
	0x07, 0xE0, 0x07, 0xC0, //      ######          #####  
	0x07, 0xF0, 0x01, 0xE0, //      #######           #### 
	0x06, 0x78, 0x00, 0x60, //      ##  ####            ## 
	0x06, 0x3C, 0x00, 0x30, //      ##   ####            ##
	0x06, 0x3C, 0x00, 0x30, //      ##   ####            ##
	0x06, 0x1E, 0x00, 0x30, //      ##    ####           ##
	0x06, 0x0F, 0x00, 0x30, //      ##     ####          ##
	0x06, 0x07, 0x80, 0x30, //      ##      ####         ##
	0x06, 0x03, 0xC0, 0x70, //      ##       ####       ###
	0x06, 0x01, 0xF0, 0xE0, //      ##        #####    ### 
	0x06, 0x00, 0xFF, 0xE0, //      ##         ########### 
	0x06, 0x00, 0x7F, 0xC0, //      ##          #########  
	0x06, 0x00, 0x1F, 0x00, //      ##            #####    

	/* @448 '3' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x60, 0x03, 0x00, //          ##           ##    
	0x01, 0xE0, 0x03, 0xC0, //        ####           ####  
	0x03, 0xE0, 0x03, 0xE0, //       #####           ##### 
	0x03, 0x80, 0x00, 0xE0, //       ###               ### 
	0x07, 0x00, 0x00, 0x70, //      ###                 ###
	0x06, 0x00, 0x00, 0x30, //      ##                   ##
	0x06, 0x00, 0xC0, 0x30, //      ##         ##        ##
	0x06, 0x00, 0xC0, 0x30, //      ##         ##        ##
	0x06, 0x00, 0xC0, 0x30, //      ##         ##        ##
	0x06, 0x00, 0xE0, 0x70, //      ##         ###      ###
	0x03, 0x01, 0xF0, 0xE0, //       ##       #####    ### 
	0x03, 0x83, 0xBF, 0xE0, //       ###     ### ######### 
	0x01, 0xFF, 0xBF, 0xC0, //        ########## ########  
	0x00, 0xFF, 0x0F, 0x00, //         ########    ####    
	0x00, 0x7C, 0x00, 0x00, //          #####              

	/* @512 '4' (16 pixels wide) */
	0x00, 0x38, 0x00, 0x00, //           ###               
	0x00, 0x3C, 0x00, 0x00, //           ####              
	0x00, 0x3F, 0x00, 0x00, //           ######            
	0x00, 0x33, 0x80, 0x00, //           ##  ###           
	0x00, 0x31, 0xE0, 0x00, //           ##   ####         
	0x00, 0x30, 0x70, 0x00, //           ##     ###        
	0x00, 0x30, 0x3C, 0x00, //           ##      ####      
	0x00, 0x30, 0x0E, 0x00, //           ##        ###     
	0x00, 0x30, 0x07, 0x80, //           ##         ####   
	0x00, 0x30, 0x01, 0xC0, //           ##           ###  
	0x07, 0xFF, 0xFF, 0xF0, //      #######################
	0x07, 0xFF, 0xFF, 0xF0, //      #######################
	0x07, 0xFF, 0xFF, 0xF0, //      #######################
	0x00, 0x30, 0x00, 0x00, //           ##                
	0x00, 0x30, 0x00, 0x00, //           ##                
	0x00, 0x30, 0x00, 0x00, //           ##                

	/* @576 '5' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x60, 0x00, 0x00, //          ##                 
	0x01, 0xE0, 0xFC, 0x00, //        ####     ######      
	0x03, 0xE0, 0xFF, 0xF0, //       #####     ############
	0x03, 0x80, 0xFF, 0xF0, //       ###       ############
	0x07, 0x00, 0x63, 0xF0, //      ###         ##   ######
	0x06, 0x00, 0x30, 0x30, //      ##           ##      ##
	0x06, 0x00, 0x30, 0x30, //      ##           ##      ##
	0x06, 0x00, 0x30, 0x30, //      ##           ##      ##
	0x06, 0x00, 0x30, 0x30, //      ##           ##      ##
	0x07, 0x00, 0x30, 0x30, //      ###          ##      ##
	0x03, 0x00, 0x70, 0x30, //       ##         ###      ##
	0x03, 0xC1, 0xE0, 0x30, //       ####     ####       ##
	0x01, 0xFF, 0xC0, 0x30, //        ###########        ##
	0x00, 0xFF, 0x80, 0x30, //         #########         ##
	0x00, 0x3F, 0x00, 0x00, //           ######            

	/* @640 '6' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x1F, 0xF8, 0x00, //            ##########       
	0x00, 0x7F, 0xFF, 0x00, //          ###############    
	0x01, 0xFF, 0xFF, 0xC0, //        ###################  
	0x03, 0xE0, 0xC7, 0xC0, //       #####     ##   #####  
	0x03, 0x80, 0x60, 0xE0, //       ###        ##     ### 
	0x07, 0x00, 0x60, 0x70, //      ###         ##      ###
	0x06, 0x00, 0x30, 0x30, //      ##           ##      ##
	0x06, 0x00, 0x30, 0x30, //      ##           ##      ##
	0x06, 0x00, 0x30, 0x30, //      ##           ##      ##
	0x06, 0x00, 0x30, 0x30, //      ##           ##      ##
	0x07, 0x00, 0x70, 0x70, //      ###         ###     ###
	0x03, 0xC1, 0xE0, 0xE0, //       ####     ####     ### 
	0x01, 0xFF, 0xC3, 0xE0, //        ###########    ##### 
	0x00, 0xFF, 0x83, 0xC0, //         #########     ####  
	0x00, 0x3F, 0x03, 0x00, //           ######      ##    

	/* @704 '7' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x30, //                           ##
	0x00, 0x00, 0x00, 0x30, //                           ##
	0x00, 0x00, 0x00, 0x30, //                           ##
	0x04, 0x00, 0x00, 0x30, //      #                    ##
	0x07, 0x80, 0x00, 0x30, //      ####                 ##
	0x07, 0xE0, 0x00, 0x30, //      ######               ##
	0x03, 0xF8, 0x00, 0x30, //       #######             ##
	0x00, 0x7F, 0x00, 0x30, //          #######          ##
	0x00, 0x1F, 0xC0, 0x30, //            #######        ##
	0x00, 0x07, 0xF8, 0x30, //              ########     ##
	0x00, 0x00, 0xFE, 0x30, //                 #######   ##
	0x00, 0x00, 0x3F, 0xB0, //                   ####### ##
	0x00, 0x00, 0x0F, 0xF0, //                     ########
	0x00, 0x00, 0x01, 0xF0, //                        #####
	0x00, 0x00, 0x00, 0x70, //                          ###

	/* @768 '8' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x78, 0x00, 0x00, //          ####               
	0x01, 0xFE, 0x0F, 0x80, //        ########     #####   
	0x03, 0xFF, 0x1F, 0xC0, //       ##########   #######  
	0x03, 0x87, 0x3F, 0xE0, //       ###    ###  ######### 
	0x07, 0x03, 0xF8, 0x60, //      ###      #######    ## 
	0x06, 0x01, 0xE0, 0x30, //      ##        ####       ##
	0x06, 0x00, 0xE0, 0x30, //      ##         ###       ##
	0x06, 0x00, 0xC0, 0x30, //      ##         ##        ##
	0x06, 0x00, 0xE0, 0x30, //      ##         ###       ##
	0x06, 0x01, 0xE0, 0x30, //      ##        ####       ##
	0x07, 0x03, 0xF8, 0x60, //      ###      #######    ## 
	0x03, 0x87, 0x3F, 0xE0, //       ###    ###  ######### 
	0x03, 0xFF, 0x1F, 0xC0, //       ##########   #######  
	0x01, 0xFE, 0x0F, 0x80, //        ########     #####   
	0x00, 0x78, 0x00, 0x00, //          ####               

	/* @832 '9' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x60, 0x7E, 0x00, //          ##      ######     
	0x01, 0xE0, 0xFF, 0x80, //        ####     #########   
	0x03, 0xE1, 0xFF, 0xC0, //       #####    ###########  
	0x03, 0x83, 0xC1, 0xE0, //       ###     ####     #### 
	0x07, 0x07, 0x00, 0x70, //      ###     ###         ###
	0x06, 0x06, 0x00, 0x30, //      ##      ##           ##
	0x06, 0x06, 0x00, 0x30, //      ##      ##           ##
	0x06, 0x06, 0x00, 0x30, //      ##      ##           ##
	0x06, 0x06, 0x00, 0x30, //      ##      ##           ##
	0x07, 0x03, 0x00, 0x70, //      ###      ##         ###
	0x03, 0x83, 0x00, 0xE0, //       ###     ##        ### 
	0x01, 0xF1, 0x83, 0xE0, //        #####   ##     ##### 
	0x01, 0xFF, 0xFF, 0xC0, //        ###################  
	0x00, 0x7F, 0xFF, 0x00, //          ###############    
	0x00, 0x0F, 0xFC, 0x00, //             ##########      

	/* @896 ':' (16 pixels wide) */
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x07, 0x00, 0x1C, 0x00, //      ###           ###      
	0x07, 0x00, 0x1C, 0x00, //      ###           ###      
	0x07, 0x00, 0x1C, 0x00, //      ###           ###      
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
	0x00, 0x00, 0x00, 0x00, //                             
};
