

#define SBUS_FRAME_SIZE		25
#define SBUS_INPUT_CHANNELS	16

//SBUS 输出范围
#define SBUS_RANGE_MIN 200.0f
#define SBUS_RANGE_MAX 1800.0f

#define SBUS_FRAME_HEADER 0x0f
#define SBUS_FRAME_FOOTER 0x00

#define SBUS_STATE_FAILSAFE 0x08
#define SBUS_STATE_SIGNALLOSS 0x04




#define SBUS_TARGET_MIN 1000.0f
#define SBUS_TARGET_MAX 2000.0f

/* pre-calculate the floating point stuff as far as possible at compile time */
#define SBUS_SCALE_FACTOR ((SBUS_TARGET_MAX - SBUS_TARGET_MIN) / (SBUS_RANGE_MAX - SBUS_RANGE_MIN))
#define SBUS_SCALE_OFFSET (int32_t)(SBUS_TARGET_MIN - (SBUS_SCALE_FACTOR * SBUS_RANGE_MIN + 0.5f))

//#define SBUS_CHANNEL_MAX	6  //遥控器使用的通道数


void USART2_Send_DMA(u8 *bytes, u8 bytes_len);
void sbus_init(void);
void USART2_Send(unsigned char *tx_buf, int len);
void UART2_Send(unsigned char tx_buf);
void sbus_output(void);
void sbus_out(uint16_t num_values);
