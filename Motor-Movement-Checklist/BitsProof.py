#!/usr/bin/env python3
#
# Carpenter Software
# File: Motor-Movement-Checklist/BitsProof.py
# Github: MageMCU
# Repository: Joystick-Uno-L298N
#
# By Jesse Carpenter (carpentersoftware.com)
#
# MIT LICENSE
#
# Added 20261017. Written with Claude (Anthropic), an AI assistant.
# Revised 20261018 (v3.1.0): Step1_JUL reads x on A0 and y on A1; the
# model and the table are unchanged, because the orientations are
# counted from the shipped lines, whichever pins they name.
#
# PURPOSE
#   Checks that one Bits() value corrects every bench, whatever the
#   analog pins, the analogRead() equations, and the L298N connections.
#   The program models Step1_JUL with its shipped lines,
#       xDigital = analogRead(A0);  yDigital = analogRead(A1);
#   and runs the Motor Movement Checklist search, bits_0000 upward,
#   for each of 128 benches:
#     8 joystick orientations: VRx and VRy exchanged on A0 and A1
#       (swap), x reversed
#       (xR), y reversed (yR)
#     16 L298N wirings: enable pins crossed (E), motors exchanged
#       between the two channels (M), left motor leads reversed (L),
#       right motor leads reversed (R)
#   A value passes when both wheels turn as the joystick algorithm
#   intends (within 1 count of 255) over a grid of stick positions.
#
# MODEL (the same rules as the code)
#   Joystick.h  octant algorithm, tolerance 0.001
#   Step1_JUL   map 0..1023 to -1..1, center offsets X 0.05 and Y 0.06,
#               map -1..1 to -255..255 with an (int) cast
#   L298N.h     Bits(): bit 3 EN, bit 2 PWM, bit 1 LeftIN, bit 0 RightIN
#
# USE
#   python3 BitsProof.py            prints the 16 x 8 table
#   python3 BitsProof.py example    one random bench, step by step
#   python3 BitsProof.py connections  all 720 ways to connect D5 to D10
#
# RESULT (20261017): every one of the 128 benches has exactly one
# passing value, and each of the 16 values serves 8 benches. Of the
# 720 ways to connect D5 to D10 to the six L298N inputs, the 16 that
# keep the rules of Step1_JUL (end of main.cpp) are corrected for all
# 8 joystick orientations; none of the other 704 is.

import itertools
import random
import sys


def joystick(x, y):
    # Joystick.h, revised algorithm
    tol = 0.001
    ax, ay = abs(x), abs(y)
    d = abs(ax - ay)
    if ax < tol and ay < tol:
        return 0.0, 0.0
    if ax >= ay:
        if x >= 0 and y >= 0:
            return x, -d
        if x <= 0 and y >= 0:
            return -d, -x
        if x <= 0 and y <= 0:
            return x, d
        return d, -x
    if x >= 0 and y >= 0:
        return y, d
    if x <= 0 and y >= 0:
        return d, y
    if x <= 0 and y <= 0:
        return y, -d
    return -d, y


def unit(v):
    # LinearMap<float>(0, 1023, -1.0, 1.0)
    return -1.0 + 2.0 * v / 1023.0


def l298n(left, right, bits):
    # L298N::UpdateL298N(); Uno pins D5 to D10 in the class order
    en, pwm, lin, rin = (bits >> 3) & 1, (bits >> 2) & 1, (bits >> 1) & 1, bits & 1
    ena, enb = (5, 10) if en else (10, 5)
    a, b = (left, right) if pwm else (right, left)
    pins = {}

    def pair(value, flag, pin_a, pin_b):
        set1 = (value >= 0) == bool(flag)  # _LeftSet1(): A LOW, B HIGH
        pins[pin_a], pins[pin_b] = (0, 1) if set1 else (1, 0)

    pair(a, lin, 6, 7)
    pair(b, rin, 8, 9)
    pins[ena] = abs(a)
    pins[enb] = abs(b)
    return pins


def wheels(pins, wiring):
    # The module: channel 1 = EN from D5 (D10 if crossed), IN1 and IN2
    # from D6 and D7; channel 2 = EN from D10 (D5), IN3 and IN4 from D8, D9
    e, m, lrev, rrev = wiring
    ch1 = pins[10 if e else 5] * (1 if pins[6] else -1)
    ch2 = pins[5 if e else 10] * (1 if pins[8] else -1)
    left, right = (ch2, ch1) if m else (ch1, ch2)
    return (-left if lrev else left, -right if rrev else right)


def readings(u, v, orient):
    # True stick (u to the right, v forward) to the readings
    # (xDigital on A0, yDigital on A1)
    swap, xr, yr = orient
    a, b = (v, u) if swap else (u, v)
    if xr:
        a = 1023 - a
    if yr:
        b = 1023 - b
    return a, b


def step1_jul(x_digital, y_digital, bits):
    x, y = unit(x_digital), unit(y_digital)
    if abs(x) < 0.05:
        x = 0.0
    if abs(y) < 0.06:
        y = 0.0
    left, right = joystick(x, y)
    return l298n(int(left * 255), int(right * 255), bits)


def intended(u, v):
    left, right = joystick(unit(u), unit(v))
    return int(left * 255), int(right * 255)


POINTS = [(u, v) for u in range(0, 1024, 17) for v in range(0, 1024, 19)
          if abs(unit(u)) > 0.07 and abs(unit(v)) > 0.07]
ORIENTS = list(itertools.product([0, 1], repeat=3))
WIRINGS = list(itertools.product([0, 1], repeat=4))
CHECKLIST = [("Right Turn", 1023, 511), ("North-East", 1023, 1023),
             ("Forward", 511, 1023), ("North-West", 0, 1023),
             ("Left Turn", 0, 511), ("South-West", 0, 0),
             ("Backward", 511, 0), ("South-East", 1023, 0)]


def passes(orient, wiring, bits, points=POINTS):
    for u, v in points:
        got = wheels(step1_jul(*readings(u, v, orient), bits), wiring)
        if max(abs(g - e) for g, e in zip(got, intended(u, v))) > 1:
            return False
    return True


def name_orient(o):
    parts = [n for n, f in zip(("swap", "xR", "yR"), o) if f]
    return " ".join(parts) or "normal"


def name_wiring(w):
    return ",".join(n for n, f in zip("EMLR", w) if f) or "standard"


def table():
    counts = []
    print("| Wiring | " + " | ".join(name_orient(o) for o in ORIENTS) + " |")
    print("|---" * (len(ORIENTS) + 1) + "|")
    for w in WIRINGS:
        row = []
        for o in ORIENTS:
            ok = [b for b in range(16) if passes(o, w, b)]
            counts.append(len(ok))
            row.append("/".join(f"{b:04b}" for b in ok) or "NONE")
        print(f"| {name_wiring(w)} | " + " | ".join(row) + " |")
    print()
    print(f"benches: {len(counts)}, exactly one value: {counts.count(1)}, "
          f"none: {counts.count(0)}, more than one: {sum(c > 1 for c in counts)}")


def example():
    o, w = random.choice(ORIENTS), random.choice(WIRINGS)
    print(f"Joystick: {name_orient(o)}   L298N wiring: {name_wiring(w)}")
    for b in range(16):
        for n, u, v in CHECKLIST:
            got = wheels(step1_jul(*readings(u, v, o), b), w)
            exp = intended(u, v)
            if max(abs(g - e) for g, e in zip(got, exp)) > 1:
                print(f"bits_{b:04b}: fails at {n}, wheels {got}, expected {exp}")
                break
        else:
            print(f"bits_{b:04b}: passes all eight positions")
            for n, u, v in CHECKLIST:
                xd, yd = readings(u, v, o)
                got = wheels(step1_jul(xd, yd, b), w)
                print(f"  {n:11s} stick ({u:4d}, {v:4d})  A0 {xd:4d}  A1 {yd:4d}"
                      f"  wheels {got}  intended {intended(u, v)}")
            return


def connections():
    # All 720 ways of connecting Uno pins D5 to D10 to the six L298N
    # inputs, each with the 8 joystick orientations; motor A on OUT1
    # and OUT2, motor B on OUT3 and OUT4 (the other motor placements
    # are rows M, L, and R of the table).
    names = ["ENA", "IN1", "IN2", "IN3", "IN4", "ENB"]
    pts = [(u, v) for u in range(0, 1024, 128) for v in range(0, 1024, 128)
           if abs(unit(u)) > 0.07 and abs(unit(v)) > 0.07]
    pts += [(u, v) for _, u, v in CHECKLIST]

    def channel(level, en, ia, ib):
        if level[ia] == level[ib]:
            return 0 if level[en] == 0 else None  # brake: not a drive state
        return level[en] * (1 if level[ia] else -1)

    def solvable(wire, orient):
        for b in range(16):
            good = True
            for u, v in pts:
                pins = step1_jul(*readings(u, v, orient), b)
                level = {n: pins[wire[n]] for n in names}
                left = channel(level, "ENA", "IN1", "IN2")
                right = channel(level, "ENB", "IN3", "IN4")
                exp = intended(u, v)
                if left is None or right is None or \
                        max(abs(left - exp[0]), abs(right - exp[1])) > 1:
                    good = False
                    break
            if good:
                return True
        return False

    ok_rules = bad_rules = ok_other = 0
    for perm in itertools.permutations([5, 6, 7, 8, 9, 10]):
        wire = dict(zip(names, perm))
        rules = ({wire["ENA"], wire["ENB"]} == {5, 10} and
                 {wire["IN1"], wire["IN2"]} in ({6, 7}, {8, 9}))
        ok = all(solvable(wire, o) for o in ORIENTS)
        if rules:
            ok_rules += ok
            bad_rules += not ok
        else:
            ok_other += ok
    print(f"connections keeping the rules: 16, corrected: {ok_rules}, "
          f"not corrected: {bad_rules}")
    print(f"other connections: 704, corrected: {ok_other}")


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "example":
        example()
    elif len(sys.argv) > 1 and sys.argv[1] == "connections":
        connections()
    else:
        table()
