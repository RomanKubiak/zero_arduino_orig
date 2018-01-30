#!/usr/bin/lua

local I2C = require('periphery').I2C

local i2c = I2C("/dev/i2c-1")
local r = { { 0x00,flags=I2C.I2C_M_RD} }
i2c:transfer(0x2a, r)
print(r[1][1]);

local w = { { 0xaa, 0xbb } }
i2c:transfer(0x2a, w)

i2c:close()
