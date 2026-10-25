#!/bin/zsh
# File              : install_userdata.sh
# License           : see LICENSE.txt in the root dir. If there is none, it's GPLv3
# Author            : Jonas Gilbricht <jonas.g.jobs@gmail.com>
# Date              : 25.10.2026
# Last Modified Date: 25.10.2026
# Last Modified By  : Jonas Gilbricht <jonas.g.jobs@gmail.com>
# Copyright (c) 2026 Jonas Gilbricht

cp -r ./sample_userdata $XDG_DATA_HOME
mv $XDG_DATA_HOME/sample_userdata $XDG_DATA_HOME/kanjipracticer
