#!/usr/bin/lua

rs232 = require("rs232")

local e,p = rs232.open("/dev/ttyUSB0")

if e ~= rs232.RS232_ERR_NOERROR then
	print("error")
	return
end

-- set port settings
assert(p:set_baud_rate(rs232.RS232_BAUD_115200) == rs232.RS232_ERR_NOERROR)
assert(p:set_data_bits(rs232.RS232_DATA_8) == rs232.RS232_ERR_NOERROR)
assert(p:set_parity(rs232.RS232_PARITY_NONE) == rs232.RS232_ERR_NOERROR)
assert(p:set_stop_bits(rs232.RS232_STOP_1) == rs232.RS232_ERR_NOERROR)
assert(p:set_flow_control(rs232.RS232_FLOW_OFF)  == rs232.RS232_ERR_NOERROR)

print(string.format("OK, port open with values '%s'\n", tostring(p)))
err, len = p:write(":head\r\n")
assert (err == rs232.RS232_ERR_NOERROR)
print("reading")
err, data = p:read(16, 100)
print(string.format("got data %s", data))
p:close()