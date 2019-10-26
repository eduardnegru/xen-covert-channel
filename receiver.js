const os = require('os-utils');
const perf = require('execution-time')();
const process = require('process');

function start_receiver()
{
    console.log("Receiving");
}

(async () => {

    let i = 0;
    let start = new Date().getTime();
    
    while(true)
    {
        i++;
        let end = new Date().getTime();
        if(end - start === 1000)
        {
            break;
        }
    }

    console.log("Executed", i);



    // let timer = setInterval(()=> {
        
    //     let date = new Date();
    //     let seconds = date.getSeconds();
    //     let miliseconds = date.getMilliseconds();

    //     if (seconds === 0 && miliseconds === 0)
    //     {
    //         clearInterval(timer);
    //     }

    // }, 1);

})();