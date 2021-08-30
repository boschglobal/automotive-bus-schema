<!---
  Copyright (c) 2021 for information on the respective copyright owner
  see the NOTICE file and/or the repository https://github.com/boschglobal/automotive-bus-schema

  SPDX-License-Identifier: Apache-2.0
-->

# Contributing to Automotive Bus Schema

First off, thanks for taking the time to contribute!

Any contribution is welcome, e.g. documentation, bug reports, feature requests, issues, blog posts, tutorials, feature implementation, etc. You can contribute code or documentation through the standard GitHub pull request model. For large contributions we do encourage you to file a ticket in the GitHub issue tracking system prior to any development to coordinate with the Automotive Bus Schema development team early in the process. Coordination up front helps to avoid frustration later on.

The following is a set of guidelines for contributing to Automotive Bus Schema and its packages, which are hosted on GitHub [boschglobal/automotive-bus-schema](https://github.com/boschglobal/automotive-bus-schema). These are mostly guidelines, not rules. Use your best judgment, and feel free to propose changes to this document in a pull request.

## Table Of Contents

[How can I contribute?](#how-can-i-contribute)

- [Reporting Bugs](#reporting-bugs)
- [Suggesting Enhancements](#suggesting-enhancements)
- [Contribution requirements](#contribution-requirements)
- [Pull Requests](#pull-requests)

[Styleguides](#styleguides)

- [Git Commit Messages](#git-commit-messages)
- [FlatBuffers Styleguide](#flatbuffers-styleguide)
- [Documentation Styleguide](#documentation-styleguide)

## How can I contribute?

### Reporting Bugs

- If you find anything, which does not work as expected, feel free to [file an issue](https://github.com/boschglobal/automotive-bus-schema/issues). Please be sure to describe in the ticket, what you expected, what the actual result was and the steps to reproduce the issue (in case it can be reproduced, and it's no runtime related issue).

### Suggesting Enhancements

- If you are missing some functionality, your suggestion is highly welcome. Please feel free to file the suggestion in our Backlog. This is no guarantee, that we will implement it asap, but we will have a look at it and decide whether we have the capacity to add this feature in the future. The priority, in which features will be added is decided by our product owner.

Note: we won't tailor the schemas to be an exact solution for a single problem, if that's the only purpose of your suggestion. We can assist you in identifing a sales person if you would like to start an assisted integration project.

### Contribution requirements

- Create a fork and contribute using feature branches
- Cool, you already actually implemented something, which brings the platform to the next level. We highly appreciate collaborative work. Did you already go through our [Styleguides](#Styleguides) to make sure your contribution fits to the rest of the codebase?<br>
  You rebased your feature branch onto our develop-branch, and it works with the latest commit? If yes, it's time for your pull request.
- Create a pull-request [here](https://github.com/boschglobal/automotive-bus-schema/pulls)
- __EVERY__ commit in your pull request needs to be signed. By signing of your commits you certify that you can contribute code according to the requirements of the [styleguides](#styleguides). Simply speaking you certify that you are the creator of the code or have the rights to contribute under the Apache-2.0 license
  - If you have set your `user.name` and `user.email` git configs you can automatically sign the commit by running the git-commit command with the `-s` option. There may be multiple sign-offs if more than one developer was involved in authoring the contribution.

### Pull requests

- Please always make sure, that your branch is properly rebased on the develop branch and that it does not have any unresolved conflicts
- We chose pull requests as our point of interaction with all our contributors. We will review your changes and comment on that.
- If we have something to improve before merge, we will comment your pull request.
- It will stay open, until it is ready to merge
- Please be patient. We have many things to do and only work during common business hours in our Timezone (+01:00 GMT)

## Styleguides

### Git commit messages

- All commits within your pull request should contain, what you actually did. A developer should be able to roughly figure out, what you've done, when he reads through your message.
- If you have a User-Story or a bug ticket, prepend this in front of the commit message.
- Always write in present as if the "commit does something to the codebase" e.g. If I execute this commit it will "Define more features in the Automotive Bus Schema"
- Avoid statements like for any commit:
  - Things done
  - Minor fixes
  - Improvements made
  - Small fixes
  - Enhanced performance

### FlatBuffers Styleguide

- We use the Google FlatBuffers style guide rules in the Google FlatBuffers Programmer's Guide. Please refer to the section "Style guide" in ["Writing a Schema"](https://google.github.io/flatbuffers/flatbuffers_guide_writing_schema.html).

### Documentation Styleguide

- We use Markdown for our documentation
- As of readme document, these have to be called README.md
- We are linting our files using markdownlint as VS Code Extension. The configuration can be found in the file _.markdownlintrc_ and must remain unchanged
  - To have a better understanding about the different rules, see [here](https://github.com/DavidAnson/markdownlint/blob/main/doc/Rules.md) for further information
- For javascript code documentation we use jsdoc with enabled markdown styles
