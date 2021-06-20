#include "bluetooth.h"

#define BT_BUFFER_SIZE 20
#define BT_FRAME_DATA_SIZE 4
#define BT_START_BYTE 0xFF
#define BT_END_BYTE 0xDD
#define START_BYTE_INDEX 0
#define END_BYTE_INDEX (BT_FRAME_DATA_SIZE + 2)

uint8_t bt_buffer[BT_BUFFER_SIZE];

uint16_t current_read_byte;
uint16_t current_process_byte;

void bluetooth_Init()
{
	current_read_byte = 0;
	current_process_byte = 0;
}

void bluetooth_IRQHandler()
{
	bt_buffer[current_read_byte] = USART6->DR;
	if(++current_read_byte==BT_BUFFER_SIZE)
		current_read_byte = 0;
}

uint16_t _difference;
uint16_t bytes_to_process()
{
	uint16_t difference	= abs((int32_t)current_process_byte-(int32_t)current_read_byte);
	if(current_process_byte>current_read_byte)
		difference = BT_BUFFER_SIZE-difference;
	_difference = difference;
	return difference;
}

void build_frame(uint8_t* frame)
{
	uint16_t current_build_frame_byte = current_process_byte;
	uint8_t tmp_current_frame_byte=0;
	while(tmp_current_frame_byte<(BT_FRAME_DATA_SIZE+3))
	{
		frame[tmp_current_frame_byte++]=bt_buffer[current_build_frame_byte++];
		current_build_frame_byte=current_build_frame_byte%BT_BUFFER_SIZE;
	}
}

uint8_t check_sum(void* buffer, uint16_t size)
{
	uint8_t sum = 0;
	for(uint16_t i=0;i<size;i++)
	{
		sum+=((uint8_t*)buffer)[i];
	}
	return sum;
}

bool check_frame(uint8_t* frame)
{
	if(frame[START_BYTE_INDEX]!=BT_START_BYTE)
		return false;
	
	if(frame[END_BYTE_INDEX]!=BT_END_BYTE)
		return false;
	
	if(check_sum(&frame[1],BT_FRAME_DATA_SIZE)!=frame[END_BYTE_INDEX-1])
		return false;
	
	return true;
}

void process_frame(uint8_t* frame)
{
	current_process_byte+=(BT_FRAME_DATA_SIZE+3);
	current_process_byte=current_process_byte%BT_BUFFER_SIZE;
	
	char str_buffer[10]={0};
	sprintf(str_buffer,"%d %d %d %d",frame[1],frame[2],frame[3],frame[4]);
	ssd1306_SetCursor(0,0);
	ssd1306_WriteString(str_buffer,Font_7x9,White);
	ssd1306_UpdateScreen();
}

uint8_t frame[BT_FRAME_DATA_SIZE+3];
void bluetooth_CommandsHandler()
{
	while(bytes_to_process()>=(BT_FRAME_DATA_SIZE+3))
	{
		build_frame(frame);
		if(check_frame(frame)!=true)
			current_process_byte++;
		else
			process_frame(frame);
		current_process_byte=current_process_byte%BT_BUFFER_SIZE;
	}
}


















//uint8_t bt_buffer[4]={0};
//volatile uint8_t current_byte;
//volatile uint32_t last_byte_time;

//uint16_t commands[COMMANDS_BUFFER_SIZE][3];
//volatile uint8_t current_receive_command;
//volatile uint8_t current_process_command;


//extern uint16_t max_value[PAGE_COUNT][LINE_COUNT];
//extern UART_HandleTypeDef huart6;
//extern char parameters_names[PAGE_COUNT][LINE_COUNT][13];


////#define START_BYTE 0x7A
////#define STOP_BYTE 0x12
////#define BT_FRAME_DATA_SIZE 4
////typedef struct{
////	uint8_t start_byte;
////	uint8_t data[BT_FRAME_DATA_SIZE];
////	uint8_t summ;
////	uint8_t stop_byte;
////}bt_frame;
////
////typedef union{
////	bt_frame frame;
////	uint8_t buffer[sizeof(bt_frame)];
////}bt_frame_u;
////#define FRAME_BUFFER_SIZE 100
////bt_frame_u frames[FRAME_BUFFER_SIZE];
////
////volatile uint8_t current_byte;
////volatile uint32_t last_byte_time;
////volatile uint8_t current_receive_frame;
////volatile uint8_t current_process_frame;

//void bluetooth_Init()
//{
//	//current_receive_frame=0;
//	//current_process_frame=0;
//	current_receive_command=0;
//	current_process_command=0;
//	current_byte = 0;
//}

//uint8_t checkSum(uint8_t data[])
//{
//	return 0;
//}

//void bluetooth_IRQHandler()
//{
//	if(HAL_GetTick()-last_byte_time>10)
//		current_byte = 0;
//	
//	bt_buffer[current_byte] = USART6->DR;
//	//frames[current_receive_frame].buffer[current_byte] = USART6->DR;
//	current_byte++;
//	if(current_byte>=3)
//	{
//		//if(frames[current_receive_frame].frame.start_byte == START_BYTE 
//		//	&& frames[current_receive_frame].frame.stop_byte == STOP_BYTE
//		//	&& checkSum(frames[current_receive_frame].frame.data)==frames[current_receive_frame].frame.summ)
//		//{
//		//	current_byte = 0;
//		//}
//		
//		current_byte=0;
//		commands[current_receive_command][0] = (uint16_t)bt_buffer[0];
//		commands[current_receive_command][1] = (uint16_t)bt_buffer[1];
//		((uint8_t*)(commands[current_receive_command]))[4] = bt_buffer[2];
//		((uint8_t*)(commands[current_receive_command]))[5] = bt_buffer[3];
//		
//		current_receive_command++;
//		if(current_receive_command>=COMMANDS_BUFFER_SIZE)
//			current_receive_command = 0;
//		
//	}
//	last_byte_time = HAL_GetTick();
//}

//void bluetooth_ProcessCommand(uint16_t command[3])
//{
//	uint8_t answer[128];
//	if(command[0]<PAGE_COUNT && command[1]<LINE_COUNT)
//	{
//		if(command[2]%2==0 && command[2] <= max_value[command[0]][command[1]])
//		{
//			if(Settings.parameters.current_page == command[0] && Settings.parameters.current_line == command[1])
//				TIM1->CNT = command[2];
//			Settings.values[command[0]][command[1]] = command[2];
//			
//			sprintf((char*)answer,"\n%s set %d - Ok\n",parameters_names[command[0]][command[1]],command[2]);
//			HAL_UART_Transmit(&huart6,answer,strlen((char*)answer),200);
//		}
//		else
//		{
//			sprintf((char*)answer,"\n%s set %d - Error. Only even values.\n",parameters_names[command[0]][command[1]],command[2]);
//			HAL_UART_Transmit(&huart6,answer,strlen((char*)answer),200);
//		}
//	}
//	else
//	{
//		sprintf((char*)answer,"\nCommand error. Received: %02X %02X %02X\n",command[0],command[1],command[2]);
//		HAL_UART_Transmit(&huart6,answer,strlen((char*)answer),200);
//	}
//	updateMenu();
//}

//void bluetooth_CommandsHandler()
//{
//	while(current_process_command!=current_receive_command)
//	{
//		bluetooth_ProcessCommand(commands[current_process_command]);
//		current_process_command++;
//		if(current_process_command>=COMMANDS_BUFFER_SIZE)
//			current_process_command = 0;
//	}
//}


