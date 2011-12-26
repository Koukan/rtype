all	:
	make -C client/

clean	:
	make clean -C client/

fclean	:
	make fclean -C client/

re	: fclean all
