#!/usr/bin/python

import subprocess
from scipy import stats
import argparse
import numpy as np

def parseArguments():
  parser = argparse.ArgumentParser()

  parser.add_argument("lambd", type=float)
  parser.add_argument("mu", type=float)
  parser.add_argument("simtime", type=float)
  parser.add_argument("queueSize", type=int)
  parser.add_argument("--alpha", type=float, default=0.01)
  parser.add_argument("--beta", type=float, default=0.1)
  parser.add_argument("--runMode", type=str, default='static')

  return parser.parse_args()

def executeProgram(run, args): #run ~ seed
  result = subprocess.Popen("../src/scenario {} {} {} {} {}".format(run, args.lambd, args.mu, args.simtime, args.queueSize),
            shell=True, stdout = subprocess.PIPE).stdout.read().split(" ")
  servTimes = float(result[1])
  plr = float(result[5])
  return [servTimes, plr]

def confidenceInterval (serviceTimes, plr, alpha):
  return [np.sqrt(np.var(serviceTimes, ddof=1)) / np.sqrt(len(serviceTimes)) * stats.t.ppf(1-alpha/2, len(serviceTimes)-1),
  np.sqrt(np.var(plr, ddof=1)) / np.sqrt(len(plr)) * stats.t.ppf(1-alpha/2, len(plr)-1)]


def main():
  args = parseArguments()

  serviceTimes = []
  PLR = []

  if (args.runMode == "dynamic"):
    for run in range(1, 3):
      serviceTimes += [executeProgram(run, args)[0]]
      PLR += [executeProgram(run, args)[1]]

    run = 2
    while (confidenceInterval (serviceTimes, PLR, args.alpha) > args.beta):
      run = run + 1
      serviceTimes += [executeProgram(run, args)[0]]
      PLR += [executeProgram(run, args)[1]]
  elif (args.runMode == "static"):
    for run in range(1, 11):
      serviceTimes += [executeProgram(run, args)[0]]
      PLR += [executeProgram(run, args)[1]]
  else:
    print ("Wrong runMode, variants: static dynamic")
    exit (1)
  print ("{} {} {} {} {} {}".format (args.lambd / args.mu, args.queueSize, np.mean(serviceTimes), np.mean(PLR), confidenceInterval(serviceTimes, PLR, args.alpha)[0],  confidenceInterval(serviceTimes, PLR, args.alpha)[1]) )

if __name__ == "__main__":
  main()
