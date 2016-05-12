---
layout: post
title: "Mini-project: Horizontally scale a web service using Docker"
---

*Estimated Duration:* 2-4 hours

*Author:* Will Price, Codemanship

*Language(s)/stacks:* Any, Docker

*Goal:* Produce a simple web service that is easily overwhelmed by multiple
concurrent requests.  To handle more concurrent users run multiple instances of
the service behind a reverse proxy to abstract away which instance you are
querying. Dynamically scale the number of instances of the service whilst
updating the reverse proxy configuration.

## Summary:

Create a web service in your favourite language with the following end point
GET `/is_prime/<integer>` that responds with the JSON: 

    { "integer": 1234, "is_prime": false }

Do this using the square root search method: iterate a candidate factor variable
up to the square root of the integer, for each number checking whether the
remainder of the integer divided by the candidate factor is zero (if it is, then
it is a factor), this has the worst case complexity O(\sqrt(n)).

* Dockerise your web service
* Run multiple instances of your web service and manually configure a reverse
  proxy to allocate requests using [round robin](https://en.wikipedia.org/wiki/Round-robin_scheduling) scheduling.
* Dynamically configure the reverse proxy based on the running containers using
  [Docker-gen](https://github.com/jwilder/docker-gen)


## Continuous Integration Extension:

* Build a container on each commit to your git repository using travis, jenkins,
  your favourite CI server.
* On a successful image build, push that image to the docker registry from your
  CI server.


## Example
See my own attempt on [github](https://github.com/willprice/horizontally-scaling-webservices-using-docker)
