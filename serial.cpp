#include "zero.h"
#include "commands.h"

char serial_rcv_buffer[SERIAL_BUFFER_SIZE];
bool serial_new_command_ready = false;
bool serial_processing_text = true;

void serial_process_text()
{
    DBG("now");
    if (serial_rcv_buffer[0] == ':')
        command_process(&serial_rcv_buffer[0]);
        
    serial_new_command_ready = false;
}

void serial_process_binary()
{
    DBG("now");
    serial_new_command_ready = false;
}

void serial_process()
{
    static byte ndx = 0;
    char rc;

    while (Serial.available() > 0 && serial_new_command_ready == false)
    {
        rc = Serial.read();
        if (rc != 0xd)
        {
            serial_rcv_buffer[ndx] = rc;
            ndx++;
            if (ndx >= SERIAL_BUFFER_SIZE)
            {
                ndx = SERIAL_BUFFER_SIZE - 1;
            }
        }
        else
        {
            serial_rcv_buffer[ndx] = '\0'; // terminate the string
            ndx = 0;
            serial_new_command_ready = true;
        }
    }
    if (serial_new_command_ready)
    {    
    	if (serial_rcv_buffer[0] == ':')
    	    serial_process_text();
    	else
            serial_process_binary();
    }
}