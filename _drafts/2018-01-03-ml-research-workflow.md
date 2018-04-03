---
layout: post
title: "ML research workflow"
---

Problem: The 'workflow' I use to answer my ML/CV research questions is very
adhoc, and lacking, sometimes I overdevelop certain aspects wasting time, don't
develop others sufficiently or don't perform enough investigation of the problem
before trying to produce a solution.

How can I improve my working strategy to better utilise time and resources
avoiding wasted work?

Let's take an example (contrived) research problem and think about how we can
craft a workflow to help produce an answer. 

> Which stream of a two stream CNN for action recognition has the greater
> predictive power for different types of actions?

What do we need to answer this question?

* An action recognition dataset
* CNN trained for action recognition
* Predictive power evaluation metric

Let's say we choose the BEOID dataset, we need to train a network for this, so
we need to choose an architecture.  To reasonably answer the question we'd
ideally survey the most popular two stream network architectures, but in this
case let's just pick one as that'll be sufficient to flesh out the workflow.
We pick [TSN](https://github.com/yjxiong/temporal-segment-networks) as our
architecture of choice. 




Notes:

Resources:

Articles:

* http://arkitus.com/patterns-for-research-in-machine-learning/
* http://dustintran.com/blog/a-research-to-engineering-workflow integrating
  papers into source code repo, using checkpoints, logging experiments, 
* http://www.theexclusive.org/2012/08/principles-of-research-code.html
* http://blog.niland.io/how-we-conduct-research-at-niland/ describes common
  pitfalls when experimenting and introduces a web based framework 'Niland lab',
  appears to be closed source.
* https://www.reddit.com/r/MachineLearning/comments/3npg0d/how_to_keep_track_of_experiments/
  "How to keep track of experiments"
* http://hmgaudecker.github.io/econ-project-templates/introduction.html Template
  for reproducible research projects
* https://stripe.com/blog/reproducible-research Stripe's approach to data
  science
* http://blog.binaryedge.io/2015/09/08/the-data-science-workflow/ BinaryEdge's
  data science workflow
* https://gitlab.idiap.ch/bob/bob.paper.icml2017 Reproducibility in Machine
  Learning Research accompanying repository
* http://blog.richardweiss.org/2016/10/13/kaggle-with-luigi.html How the Richard Weiss
  structures projects for kaggle competitions

Project structuring

* https://drivendata.github.io/cookiecutter-data-science/
* https://github.com/ThomasRobertFr/ml-project-structure
* https://github.com/uwescience/shablona
* https://github.com/tshauck/Gloo Gloo, a project management tool


Tools

> Sacred is a tool to help you configure, organize, log and reproduce
> experiments.

-- [Sacred](https://github.com/IDSIA/sacred)

> DVC is an open source tool for data science projects. DVC makes your data
> science projects reproducible by automatically building data dependency graph
> (DAG). Your code and the dependencies could be easily shared by Git, and data
> - through cloud storage (AWS S3, GCP) in a single DVC environment.

-- [dvc](https://github.com/dataversioncontrol/dvc)

> Sumatra is a tool for managing and tracking projects based on numerical
> simulation and/or analysis, with the aim of supporting reproducible research.
> It can be thought of as an automated electronic lab notebook for computational
> projects.

-- [sumatra](https://pythonhosted.org/Sumatra/)

> Studio is a model management framework written in Python to help simplify and
> expedite your model building experience. It was developed to minimize the
> overhead involved with scheduling, running, monitoring and managing artifacts
> of your machine learning experiments.

-- [studio.ml](http://studio.ml/)

> This library provides a set of tools that can be useful in many machine
> learning applications (classification, clustering, regression, etc.), and
> particularly helpful if you use scikit-learn (although this can work if you
> have a different algorithm).

-- [featureforge](https://github.com/machinalis/featureforge)

> 
> CDE delivers on one simple promise: If you can run a set of commands on your
> Linux machine, then CDE allows others to easily re-run those same commands on
> their Linux machines.

-- [CDE](http://www.pgbovine.net/cde.html)


> FGLab is a machine learning dashboard, designed to make prototyping
> experiments easier. Experiment details and results are sent to a database,
> which allows analytics to be performed after their completion

-- [FGLab](https://kaixhin.github.io/FGLab/)

> Manage your ml experiments to have all your results in one place. Pythia tries
> to give you an overview even if you have experiments running in different
> places.

-- [Pythia](https://github.com/christiansch/pythia)

> Empirical provides a standard framework for experimentation that encapsulates
> each experiment and makes them portable. By adopting this framework you will
> be able to use our platform to run and keep track of your experiments

-- [empirical](https://empiricalci.com/)

>  Pachyderm lets you deploy and manage multi-stage, language-agnostic data
> pipelines while maintaining complete reproducibility and provenance.

-- [Pachyderm](http://pachyderm.io/)

> Sake is a way to easily design, share, build, and visualize workflows with
> intricate interdependencies. Sake is self-documenting because the instructions
> for building a project also serve as the documentation of the project's
> workflow

-- [Sake](http://tonyfischetti.github.io/sake/)

> Bonobo is a data-processing toolkit for python 3.5+
> Write atomic data transformations using simple python callables.
> Connect them in a directed graph.
> Execute.

-- [bonobo](https://www.bonobo-project.org/#in-action)

> Joblib is a set of tools to provide lightweight pipelining in Python. In
> particular, joblib offers:
>
> 1. transparent disk-caching of the output values and lazy re-evaluation (memoize pattern)
> 2. easy simple parallel computing
> 3. logging and tracing of the execution

-- [joblib](https://pythonhosted.org/joblib/)

> Dask is a flexible parallel computing library for analytic computing.
> 
> Dask is composed of two components:
>
> 1. Dynamic task scheduling optimized for computation. This is similar to
>    Airflow, Luigi, Celery, or Make, but optimized for interactive computational
>    workloads.
> 2. “Big Data” collections like parallel arrays, dataframes, and lists that
>    extend common interfaces like NumPy, Pandas, or Python iterators to
>    larger-than-memory or distributed environments. These parallel
>    collections run on top of the dynamic task schedulers.

-- [dask](https://github.com/dask/dask)
