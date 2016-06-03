
dusk_log("info", "Hello, World")

local EvtKeyPress = 1
local KeyEscape = 136

local prog = dusk_get_program()

local is = dusk_get_input_system()
dusk_event_dispatcher_add_event_listener(is, EvtKeyPress, "OnKeyPress")

function OnKeyPress(key)
    dusk_log("info", "Key Pressed: " .. key)

    if (key == KeyEscape) then
        dusk_program_exit(prog)
    end
end
