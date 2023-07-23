

void memcpy(char* source, char* dest, int nbytes);

int scroll_ln(int offset);

int get_row_from_offset(int offset);

int get_offset(int col, int row);

int move_offset_to_new_line(int offset);

void set_char_at_video_memory(char ch, int offset);

unsigned char port_byte_in(unsigned short port);

void port_byte_out(unsigned short port, unsigned char data);

void set_cursor(int offset);

int get_cursor();

void print(char* str);

void clear_screen();