# Bayes-Net-Learning-EM
This repo consists the implementation of the standard Expectation-Maximisation (EM) algorithm for learning the parameters of a Bayesian Network when some data is missing. Here we would provide the inputs of the Bayesian network (with unknown parameter values) and the input graph data (with some missing values). And the final output will be the bayesian network with the learned parameters.

## Problem Situation
Some medical researchers have created a Bayesian network that models the inter-relationship between (some) diseases and observed symptoms. Our job as computer scientists is to learn parameters for the network based on health records. Unfortunately, as it happens in the real world, certain records have missing values. We need to do our best to compute the parameters for the network, so that it can be used for diagnosis later on

Here, a **.bif** format is used for the representation of these Bayesian Networks. The example input file here is **alarm.bif**. Please go through the sample input file and the link below, for a better understanding of this format http://sites.poli.usp.br/p/fabio.cozman/Research/InterchangeFormat/index.html 

The input data will be given a dat file. Here the example input is **records.dat**. The output will be the result of learning each probability value in the conditional probability tables. In other words, replaces all -1s with a probability value upto four decimal places. Thus, the output is a complete alarm.bif network

## Solution 
Compile the code by **./compile.sh** and run the code as **./run.sh alarm.bif <sample_data>.dat**. The output will be in the file **solved_alarm.bif**. The gold network parameters are saved as **gold_alarm.bif**. 
