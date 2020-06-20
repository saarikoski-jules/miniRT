#!/usr/bin/sh

while true; do
	program=$(ps aux | grep -v grep | grep -ci a.out)
	if [[ $program -gt 0 ]]; then
		lol=$(leaks a.out)
		if [[ $? -eq 1 ]]; then
			leaks a.out
		fi
	fi
	sleep 5
done
