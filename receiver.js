const os = require('os-utils');
const perf = require('execution-time')();
const process = require('process');

function start_receiver()
{
    console.log("Receiver");
      
    while(true)
    {
        let i = 0;    
        let start = new Date().getTime();

        while(true)
        {
            let end = new Date().getTime();
            i += 1;
            if(end - start > 25)
            {
                console.log("Received ", i);
                break;
            }    
        }
    }
}

(async () => {

    let timer = setInterval(()=> {
    
        let date = new Date();
        let seconds = date.getSeconds();
        let miliseconds = date.getMilliseconds();

        if (seconds === 0 && miliseconds === 0)
        {
            clearInterval(timer);
            start_receiver();
        }

    }, 1);
})();