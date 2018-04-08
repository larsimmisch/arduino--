# Overview

In this directory, we generate graphs that track the development of the
binary sizes of the generated code so that we can quickly see outliers
(or better, drastical improvements)

# sizes.py

`sizes.py` contains various functions to maintain the sizes files
and generate the HTML.

There are two sizes we keep track of:

_recent sizes_ and _git sizes_.

The recent sizes keep track of the sizes of binary files between commits.
This file (by default recent_sizes.json) is updated with each make.

The format is:

{
    "4.6.2": {
        "blink.bin": [
            {
                "index": 1, 
                "mtime": 1329313423, 
                "size": 226
            },
            {
                "index": 2, 
                "mtime": 1329313442, 
                "size": 220
            },            
        ]
    }
}

The git sizes hold the historic data of the current branch and can be updated
by calling this script with the "history" command, e.g.
python sizes/sizes.py history

(This must be done from a clean working directory i.e. one without modifications
relevant to git)

The format is:

[
    {
        "git": {
            "comment": "First cut.", 
            "short": "1a32447", 
            "hash": "1a324470852211e09f383615617d9fd0f159e385", 
            "author": "Ben Laurie", 
            "date": "2011-12-18 22:20:44 +0000", 
            "email": "ben@links.org"
        }, 
        "4.6.2": {
            "test_enc28j60.bin": 1358
        }
    }, 
    ...
]

