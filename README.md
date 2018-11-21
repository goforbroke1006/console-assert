# console-assert

Assertion tool can check actual and expected output 
of another application.


### Install

    $ bash install.sh
    
### Use it

    $ ./console-assert ./dec2bin 32 10000 2000

where 

* **./dec2bin** is testing subject
* **32** test app input (for cin)
* **10000** expected output
* **2000** is timeout in milliseconds

Return "OK" string to stdin 
and status code 0 if assert confirmed.

Return "Assertion failed!" to stderr 
and status code -100 if assertion failed.

Return info about exceeded timeout limit 
if program spend time more than defined in args.
