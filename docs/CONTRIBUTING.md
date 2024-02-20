# OpenGL C Example - Contributing Guidelines
Here are the contributing guidelines for our project. We love contributions, whether it is:
* Reporting a bug
* Discussing the current state of the code
* Submitting a fix
* Proposing new features

These guidelines aim to create a more streamlined experience for all developers working on our project.

## Issues
We use GitHub issues for bug reports and feature requests. Make sure your bug report or feature request is unique.

## Project Changes
Project changes refers to modifying the codebase in some way that requires a pull request. Here are some examples:
* Fixing a bug
* Changing a variable or method name (code refactoring)
* Adding a new feature
* Adding or modifying an asset (texture for example)

Please see the following rules for project changes below.

### Commits
- Use detailed commit messages
- Do not commit multiple features at a time (one feature should be one commit)
- Separate code refactor commits with features (perform code refactoring before or after you've already committed the feature)

### Pull Requests
All project changes need to be in the form of pull requests.

Pull request guidelines:
- Pull requests should always be reviewed by at least one other member prior to being merged
- Mark unfinished pull requests with the `wip` label
- When you start work on something you should have a pull request opened that same day or at least as soon as possible so others can be aware of the changes you are making
- You as the person opening the pull request should assign a reviewer

### Merging
Once your pull request has been `Approved` it may be merged at your discretion. In most cases responsibility for merging is left to the person who opened the pull request, however for simple pull requests it is fine for anyone to merge.

If substantive changes are made after the pull request has been marked `Approved` you should ask for an additional round of review.

- Use `squash and merge` if all commits in the PR can be summarized succinctly by a single message
- Use `rebase and merge` if each commit in the PR has its own significance
- Avoid just `merge` as it will create an extraneous merge commit

## Licensing
By contributing, you agree that your contributions will be licensed under the following:
* [ISC](https://choosealicense.com/licenses/ISC/)
