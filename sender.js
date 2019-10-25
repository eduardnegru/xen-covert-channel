var os = require('async-os-utils')

function printProgress(progress){
    process.stdout.clearLine();
    process.stdout.cursorTo(0);
    process.stdout.write(progress + '%');
}

function start_sender()
{
    console.log("Sender");
}

(async () => {

    setInterval(async () => {
        let usage = await os.cpu.usage();
        printProgress(usage);
    }, 10);

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