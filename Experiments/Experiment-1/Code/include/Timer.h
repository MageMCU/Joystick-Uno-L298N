//
// Carpenter Software
// File: Class Timer.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Experiments/Experiment-1/Code/include (copy of Code-JUL/include)
//
// By Jesse Carpenter (carpentersoftware.com)
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//

#ifndef SJUL_Uno_Timer_h
#define SJUL_Uno_Timer_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // Non-blocking interval timer based on millis().
    //
    // Two scheduling policies are provided:
    //
    //   isTimer(ms)          Schedules the next interval from the moment
    //                        the timer fires. Any loop latency accumulates
    //                        as drift. Simple and adequate for debug output,
    //                        LED blinking, and other non-critical timing.
    //
    //   isTimerFixedRate(ms) Schedules the next interval from the previous
    //                        deadline, not from the fire time. A late fire
    //                        shortens the following interval so the average
    //                        rate stays constant. Preferred for pacing
    //                        control loops (PID updates, motor commands)
    //                        where a steady sample period matters.
    //
    // The first call after construction or resetTimer() arms the timer
    // and returns false. Subsequent calls return true once per interval.
    //
    // deltaTimeSeconds() reports the measured interval, in seconds, that
    // ended at the most recent fire. With isTimer() that is the time since
    // the previous fire, so a late loop pass is visible as a value larger
    // than the nominal interval. With isTimerFixedRate() it is the time
    // since the previous deadline; see that method for what this means
    // during catch-up after a stall.
    //
    // Use one policy or the other on a given Timer object, not both.
    //
    // Standalone usage (no other header required):
    //
    //   Timer timer;
    //
    //   void loop()
    //   {
    //       // Runs once every 250 ms. No setup() step is needed; the
    //       // first call arms the timer.
    //       if (timer.isTimer(250))
    //       {
    //           // insert your timed code here
    //       }
    //   }
    //
    // Usage with Button (see Button.h). The button is sampled on every
    // pass and the timer paces the work that depends on it:
    //
    //   Timer  timer;
    //   Button button(2, 3);
    //
    //   void setup()
    //   {
    //       button.begin();
    //       // Timer needs no begin(); the first isTimer() call arms it.
    //   }
    //
    //   void loop()
    //   {
    //       // Button is sampled on every pass so debouncing works.
    //       button.updateButton();
    //
    //       // Timer runs the timed work once per interval (milliseconds).
    //       if (timer.isTimer(250))
    //       {
    //           // insert your timed code here
    //       }
    //   }
    //
    // Control-loop variant. When the interval feeds a PID update or a
    // motor command, use the fixed-rate policy so a late loop pass does
    // not stretch the sample period, and read the measured period with
    // deltaTimeSeconds():
    //
    //   void loop()
    //   {
    //       button.updateButton();
    //
    //       if (timer.isTimerFixedRate(20))
    //       {
    //           float dt = timer.deltaTimeSeconds(); // actual, not nominal
    //           // insert your timed code here, using dt as the sample period
    //       }
    //   }
    //
    // Several timers can run in the same loop(), one object per interval.
    // Never call delay() in loop(); it stalls both the button sampling and
    // every timer for its whole duration.
    class Timer
    {
    private:
        // Private Properties
        unsigned long t_previousTime; // millis() at last fire (or arm)
        unsigned long t_deltaTime;    // measured interval ending at last fire, ms
        bool t_armed;

        // Arm on first use. Returns true if the timer was just armed.
        bool arm(unsigned long now)
        {
            if (t_armed)
            {
                return false;
            }
            t_previousTime = now;
            t_armed = true;
            return true;
        }

    public:
        // Constructors
        Timer() : t_previousTime(0), t_deltaTime(0), t_armed(false) {}
        ~Timer() = default;

        // Methods

        // ------------------------------------------------------------
        // Note for readers: injecting the clock (optional exercise)
        // ------------------------------------------------------------
        // Every method below depends on a single call, millis(). If the
        // clock is supplied as a template parameter instead, the class
        // can be compiled and unit tested on a desktop (for example in a
        // PlatformIO "native" environment) against a fake clock that the
        // test advances by hand. That makes it practical to verify the
        // arming sequence, the fixed-rate catch-up, and the millis()
        // rollover without waiting 49.7 days on real hardware.
        //
        // Arduino IDE users: templates compile fine under the Arduino
        // IDE (it is the same avr-gcc compiler), and the "using Timer"
        // alias below keeps the class name and every call site
        // unchanged. What the Arduino IDE does not provide is a native
        // (desktop) build target, so the testing benefit only applies
        // under PlatformIO or a separate host toolchain. If you build
        // only with the Arduino IDE, leave the class as written; the
        // direct millis() calls are simpler and there is nothing to
        // gain from the indirection.
        //
        // Sketch of the change (not compiled here):
        //
        //   typedef unsigned long (*ClockFn)();
        //
        //   template <ClockFn clock = millis>
        //   class TimerT
        //   {
        //       // ... same members and methods as below, with each
        //       //     "millis()" replaced by "clock()" ...
        //   };
        //
        //   using Timer = TimerT<>;   // on the Uno: identical to today
        //
        // In a host test:
        //
        //   static unsigned long fakeNow = 0;
        //   unsigned long fakeMillis() { return fakeNow; }
        //
        //   TimerT<fakeMillis> t;
        //   t.isTimer(100);           // arms, returns false
        //   fakeNow = 99;  assert(!t.isTimer(100));
        //   fakeNow = 100; assert( t.isTimer(100));
        //   fakeNow = 0xFFFFFFF0UL; t.resetTimer(); t.isTimer(100);
        //   fakeNow = 0x00000054UL; assert( t.isTimer(100)); // rollover
        //
        // Caveat for the rollover test: on the ATmega328P, unsigned long
        // is 32 bits, so the subtraction wraps at 2^32 exactly as
        // millis() does. On a 64-bit desktop, unsigned long is 64 bits
        // and the same subtraction does not wrap. For the host test to
        // exercise real rollover, declare the timer's time members and
        // the fake clock as uint32_t (from <stdint.h>), which is the
        // same width as the Uno's unsigned long.
        // ------------------------------------------------------------

        // Re-arm the timer. The next isTimer() or isTimerFixedRate()
        // call starts a fresh interval. The measured interval is also
        // cleared, so deltaTimeSeconds() returns 0.0f until the timer
        // fires again.
        void resetTimer()
        {
            t_armed = false;
            t_deltaTime = 0;
        }

        // Measured interval that ended at the most recent fire, in seconds.
        // Returns 0.0f until the timer has fired at least once after
        // construction or resetTimer().
        float deltaTimeSeconds() const
        {
            return (float)t_deltaTime * 0.001f;
        }

        // Drifting policy. Returns true once each time incrementedTime
        // milliseconds have elapsed since the last fire.
        // Rollover safe: unsigned subtraction wraps correctly when
        // millis() overflows (about every 49.7 days).
        bool isTimer(unsigned long incrementedTime)
        {
            unsigned long now = millis();

            if (arm(now))
            {
                return false;
            }

            unsigned long elapsed = now - t_previousTime;
            if (elapsed >= incrementedTime)
            {
                t_deltaTime = elapsed;
                t_previousTime = now;
                return true;
            }
            return false;
        }

        // Fixed-rate policy. Returns true once each time incrementedTime
        // milliseconds have elapsed since the previous deadline. The next
        // deadline is advanced by exactly incrementedTime, so latency in
        // one cycle does not shift the schedule of later cycles.
        //
        // If the loop stalls for longer than one interval, the timer will
        // return true on consecutive calls until it has caught up, one
        // fire per missed interval. During catch-up, deltaTimeSeconds()
        // reports the time since the previous deadline, not since the
        // previous fire: the first catch-up fire reports the whole stall,
        // and each following fire reports one interval less than the one
        // before it, until the value drops below the interval and normal
        // pacing resumes. For example, after a stall of 3.5 intervals the
        // fires report 3.5, 2.5, and 1.5 intervals on three consecutive
        // loop passes. A control loop that divides by dt should treat a
        // value much larger than nominal as a stall and skip or clamp that
        // update. If catch-up is not wanted, the caller can call
        // resetTimer() after a known long stall.
        bool isTimerFixedRate(unsigned long incrementedTime)
        {
            unsigned long now = millis();

            if (arm(now))
            {
                return false;
            }

            unsigned long elapsed = now - t_previousTime;
            if (elapsed >= incrementedTime)
            {
                t_deltaTime = elapsed;
                t_previousTime += incrementedTime;
                return true;
            }
            return false;
        }
    };
}
#endif
