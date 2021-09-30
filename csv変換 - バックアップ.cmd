@echo off
mysql -h 172.16.18.254 -u user1 -pM6peZu kanjosen -e "DELETE FROM temp;"
mysql -h 172.16.18.254 -u user1 -pM6peZu kanjosen -e "DELETE FROM status;"
mysql -h 172.16.18.254 -u user1 -pM6peZu kanjosen -e "INSERT INTO status(ID) values(0);"

:loop
mysql -h 172.16.18.254 -u user1 -pM6peZu kanjosen -e "LOAD DATA INFILE '/var/lib/mysql/fortest/import/imp.csv' INTO TABLE temp FIELDS TERMINATED BY ','; " 
mysql -h 172.16.18.254 -u user1 -pM6peZu kanjosen -e "INSERT INTO status (ID,time,temper,heart) SELECT * from temp WHERE ID > (SELECT MAX(ID) FROM status);"
mysql -h 172.16.18.254 -u user1 -pM6peZu kanjosen -e "DELETE FROM temp;"
goto :loop

exit /b 0