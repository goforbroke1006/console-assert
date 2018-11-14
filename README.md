# console-interaction-tester

Assertion tool can check actual and expected output 
of another application.


### Install

    $ bash install.sh
    
### Use it

    $ console-interaction-tester ./dec2bin 32 10000

where 

* **./dec2bin** is testing subject
* **32** test app input (for cin)
* **10000** expected output

Return "OK" string to stdin 
and status code 0 if assert confirmed.

Return "Assertion failed!" to stderr 
and status code -100 if assertion failed.