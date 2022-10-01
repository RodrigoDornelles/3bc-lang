---
description: some warnings about decisions made in language development, or remarks on important considerations.
---

warnings
========

some warnings about decisions made in language development, or remarks on important considerations.

Why the codacy was removed?
-----------------
codacity was removed for showing false positives in functions with variable parameter amounts.

Why the codecov was removed?
------------------
Codecov has a bad implementation to deal with calculating coverage coefficient in projects above 99.9% where adding and removing **comments** can trigger loss of coverage error.

 * see the old history here: <https://app.codecov.io/gh/RodrigoDornelles/3bc-lang>
