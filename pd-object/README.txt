# intraconnection adc object
This is code ported from WiringPi examples for the MCP3422 adc, to be used with the MCP3424 adc on the adafruit pizero adc board.
The object will attempt to read from the adc and output a list of values when it is banged
Note: the object always outputs the list, even when there are no new values. This may change in the future (depending on what I need)