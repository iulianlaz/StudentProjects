#!/bin/bash
php create_tables.php
sqlite3 ./db/db.sqlite < ./db/import.sqlite
echo 'All tables have been populated!'
