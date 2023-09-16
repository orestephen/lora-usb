#include "at.h"

#include "ByteBuffer.h"
#include "cat.h"
#include "usbd_cdc_if.h"

static struct cat_object at;
static ByteBuffer bytebuffer;

static uint32_t frequency;

extern uint8_t rx_buffer[];
extern uint32_t rx_buffer_length;

static cat_return_state print_cmd_list(const struct cat_command *cmd) {
  return CAT_RETURN_STATE_PRINT_CMD_LIST_OK;
}

static cat_return_state freq_run(const struct cat_command *cmd) {
  // printf("frequency: %d\n", frequency);
  return 0;
}

static struct cat_variable freq_vars[] = {{
    .type = CAT_VAR_UINT_DEC,
    .data = &frequency,
    .data_size = sizeof(frequency),
    .name = "FREQUENCY",
    .access = CAT_VAR_ACCESS_READ_WRITE,
}};

/* declaring commands array */
static struct cat_command cmds[] = {
    {.name = "+freq",
     .description = "Printing something special at (X,Y).",
     .run = freq_run,
     .var = freq_vars,
     .var_num = sizeof(freq_vars) / sizeof(freq_vars[0]),
     .need_all_vars = true},
    {
        .name = "#HELP",
        .run = print_cmd_list,
    }};

/* declaring parser descriptor */
static struct cat_command_group cmd_group = {
    .cmd = cmds,
    .cmd_num = sizeof(cmds) / sizeof(cmds[0]),
};

static struct cat_command_group *cmd_desc[] = {&cmd_group};

static char buf[128];

static struct cat_descriptor desc = {.cmd_group = cmd_desc,
                                     .cmd_group_num =
                                         sizeof(cmd_desc) / sizeof(cmd_desc[0]),

                                     .buf = (uint8_t *)buf,
                                     .buf_size = sizeof(buf)};

/* custom target dependent input output handlers */
static int write_char(char ch) {
  CDC_Transmit_FS(&ch, 1);
  return 1;
}

static int read_char(char *ch) {
  return buffer_get(&bytebuffer, ch);
}

/* declaring input output interface descriptor for parser */
static struct cat_io_interface iface = {.read = read_char, .write = write_char};

uint8_t tempBuffer[128];

inline void atInit(void) {

  bytebuffer.data = tempBuffer;
  bytebuffer.size = sizeof(tempBuffer);
  buffer_clear(&bytebuffer);

  cat_init(&at, &desc, &iface, NULL);
}

inline static uint16_t buffer_setBytes(ByteBuffer* buffer, uint8_t* input, uint16_t size) {
  uint16_t i;

	if(buffer == NULL)
		return 0;
	if(buffer->position + 7 == buffer->size)
		return 0;

  for (i = 0; i + buffer->position < buffer->size; i++) {
    buffer->data[i + buffer->position] = input[i];
  }

  return i;
}

inline void atService(void) {
  if (rx_buffer_length > 0) {
    buffer_setBytes(&bytebuffer, rx_buffer, rx_buffer_length);
    CDC_Transmit_FS(rx_buffer, rx_buffer_length);
    rx_buffer_length = 0;
  }
  cat_service(&at);
}
