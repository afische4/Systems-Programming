#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/* Note that since this is a simulation, we actually use libsoftmodem
 * to create the audio data from some text messages.  We are not
 * actually reading audio data from a radio. */

#include "libsoftmodem.h"

/* To understand the overall structure here, remember the main()
 * function in m3d:
 * 
 *   char *audio;
 * 
 *   int main(int argc, char **argv)
 *   {
 *       nummsg = 0;
 *       msgpos = 0;
 *       msglen = 0;
 *       
 *       secretradio_init();
 *       audio = secretradio_get_audioloc();
 *       secretradio_register_callback(&radio_callback);
 *       secretradio_listen(0);
 *       secretradio_cleanup();
 *       
 *       return 0;
 *   }
 *
 * You notice you have a global char pointer called audio.  That
 * space is actually malloc()'d in secretradio_init() and you
 * get the pointer back in secretradio_get_audioloc().  That 
 * implies that your libsecretradio should also have a global 
 * audio char pointer.
 * 
 * Then you register a callback.  Probably your libsecretradio
 * should have that pointer global somewhere, and be able
 * to set it via secretradio_register_callback().
 * 
 * Then you have secretradio_listen(), which I provide for you
 * in part... I give you the text and some logic for handling
 * the debug types, but you need to write the supporting
 * function brk_msg().
 * 
 * The secretradio_cleanup() function just free()s the global
 * audio buffer area.
 */

char *_audio;
int _audlen;

int randint(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower; 
    return num;
}

void secretradio_init()
{
    srand(time(0));
    
    // allocate one megabyte of space for _audio
}

char * secretradio_get_audioloc()
{
    // return the global audio char buffer
}

void secretradio_register_callback(void (*f)(int audlen))
{
    // sets a global callback function pointer to the provided function f
    // you need to declare "callback" globally
    // I am testing you here on whether you know how to create a function
    // pointer.  This function itself will not change, it is just one line.
    callback = f;
}

void brk_msg(char *msg)
{
    /*
     * Here is the lion's share of the work.  This function takes a string
     * of arbitrary length, breaks it into chunks of random size, converts
     * those pieces to "audio", puts that "audio" into the global _audio
     * char buffer, and then calls the callback function.
     * 
     * Remember that you need to send the the length first in the "AABB"
     * message header string.  Start there.  Get the msg length with
     * strlen(), use sprintf() to create a string like AA6BB (where 6 is
     * the message length in this example), convert it to audio with
     * libsoftmodem, memcpy() the audio data to _audio, and then call the
     * callback.
     * 
     * After that you need to send the message itself in randomly-sized
     * chunks.  Don't try to break up the whole message at once though.
     * Pick a random integer between 1 and the remaining amount of the
     * message.  Then get the audio for that using libsoftmodem.  Do like
     * you did for the AABB header message and put the audio data in _audio
     * and call the callback.  Repeat until the whole message is sent.
     */
    
       int cpid;
    
    int sockfd, portno, n, i;
    struct sockaddr_in serv_addr;
    struct hostent *server;     
    
    int len = strlen(msg);
    int n
    int ri = rand() % max - min + 1
    char * buf = malloc
    sprintf(buf, "AA%dBB", len
    n = write(sockfd, buf, strlen(buf))
then i would randomly break up the streing and write it to the socket but I ran out of time

}

void secretradio_listen(int debug)
{
    int msglen;
    int adtlen;
    char *msg;
    
    char *f451 = "\"I rarely watch the 'parlour walls' or go to races or Fun Parks. So I've lots of time for crazy thoughts, I guess. Have you seen the two-hundred-foot-long billboards in the country beyond town? Did you know that once billboards were only twenty feet long? But cars started rushing by so quickly they had to stretch the advertising out so it would last.\" \"I didn't know that!\" Montag laughed abruptly. \"Bet I know something else you don't. There's dew on the grass in the morning.\" He suddenly couldn't remember if he had known this or not, and it made him quite irritable. \"And if you look\"-she nodded at the sky-\"there's a man in the moon.\" He hadn't looked for a long time.";
    
    char *ctime1 = "Doctor Avrana Kern awoke to a dozen complex feeds of information, none of which helped her restore her memories of what had just happened or why she was groggily returning to consciousness in a cold-sleep unit. She could not open her eyes; her entire body was cramping and there was nothing in her mental space except the overkill of information assailing her, every system of the Sentry Pod clamouring to report.";
    
    char *ctime2 = "She had racked her piecemeal recollection of her species' history and found only a hierarchy of destruction: of her species devastating the fauna of planet Earth, and then turning on its own sibling offshoots, and then at last, when no other suitable adversaries remained, tearing at itself. Mankind brooks no competitors, She has explained to them — not even its own reflection.";
    
    char *jpark1 = "But now science is the belief system that is hundreds of years old. And, like the medieval system before it, science is starting not to fit the world any more. Science has attained so much power that its practical limits begin to be apparent. Largely through science, billions of us live in one small world, densely packed and intercommunicating. But science cannot help us decide what to do with that world, or how to live. Science can make a nuclear reactor, but it cannot tell us not to build it. Science can make pesticide, but cannot tell us not to use it. And our world starts to seem polluted in fundamental ways---air, and water, and land---because of ungovernable science.";
    
    char *jpark2 = "Grant knew that people could not imagine geological time. Human life was lived on another scale of time entirely. An apple turned brown in a few minutes. Silverware turned black in a few days. A compost heap decayed in a season. A child grew up in a decade. None of these everyday human experiences prepared people to be able to imagine the meaning of eighty million years - the length of time that had passed since this little animal had died.";
    
    char *simple1 = "debug";
    
    char *simple2 = "ladybug";
    
    if(debug == 1)
        brk_msg(simple1);
    
    if(debug == 2)
    {
        brk_msg(simple1);
        brk_msg(simple2);
    }
    
    if(debug == 3)
    {
        brk_msg(jpark2);
    }
    
    if(debug == 0)
    {
        brk_msg(f451);
        brk_msg(ctime1);
        brk_msg(ctime2);
        brk_msg(jpark1);
        brk_msg(jpark2);
    }
}

void secretradio_cleanup()
{
    free(_audio);
}
