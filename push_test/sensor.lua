local moduleName = ...
local M = {}
_G[moduleName] = M
M.sens_level=tmr.create()
local sens_low=33
local sens_high=34
water_lev={}
water_lev.ser_cnt=0
gpio.config({gpio={sens_low,sens_high}, dir=gpio.IN,pull=gpio.PULL_DOWN})
function M.sens_send_water_level(boot)
	if (gpio.read(sens_high)==1 and gpio.read(sens_low)==1) then
		water_lev.water_level=false
		--water_lev.ser_cnt=water_lev.ser_cnt+1
		water_lev.error=0xff
		publish_level_data()
	elseif gpio.read(sens_high)==1 then
	    water_lev.water_level=100
		water_lev.ser_cnt=water_lev.ser_cnt+1
		water_lev.error=0
		publish_level_data()
	elseif gpio.read(sens_low) == 1 then
		water_lev.water_level=10
		water_lev.ser_cnt=water_lev.ser_cnt+1
		water_lev.error=0
		publish_level_data()
	else
		print"everything okay"
		if boot then
			water_lev.water_level=100
			--water_lev.ser_cnt=water_lev.ser_cnt+1
			water_lev.error=0
			publish_level_data()
		end
	end
	if water_lev.ser_cnt==255 then
		water_lev.ser_cnt=0
	end
end
M.sens_level:register(30000, tmr.ALARM_AUTO, function() M.sens_send_water_level() M.sens_level:start() end )
function publish_level_data()
	if mqtt_status~=0 then
		ok, json = pcall(sjson.encode, water_lev)
		MQTT_1.publish(json)
	else
		print("no wifi",water_lev.water_level)
	end
end
return M