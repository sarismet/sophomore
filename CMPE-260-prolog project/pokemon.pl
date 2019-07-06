	:- [pokemon_data].

	% ismet Sarı
	% 2016400324
	% compiling: yes
	% complete: yes

	% this predicate is designed to find the EvolvedPokemon if the Pokemon has reached out minimum level needed
    	% find_pokemon_evolution(+PokemonLevel, +Pokemon, -EvolvedPokemon).
     	  find_pokemon_evolution(PokemonLevel, Pokemon, EvolvedPokemon):-
	  find_pokemon_evolution2(PokemonLevel, Pokemon,EvolvedPokemon).

	% this predicate is designed to assist find_pokemon_evolution predicate and the level is adequate to evolve then I used esitlee predicate
	% find_pokemon_evolution2(+PokemonLevel, +Pokemon,-EvolvedPokemon).
	  find_pokemon_evolution2(PokemonLevel, Pokemon,EvolvedPokemon):-
	  (pokemon_evolution(Pokemon,EvolvedPokemonTemp,H),islessThen(H,PokemonLevel),
	  find_pokemon_evolution2(PokemonLevel,EvolvedPokemonTemp,EvolvedPokemon));esislee(EvolvedPokemon,Pokemon).
	
	% this predicate is designed to see whether the level of Pokemon is satisfied to evolve. If it is so then it returns true, if it is not so it returns false.
	% islessThen(+H,+PokemonLevel).
	  islessThen(H,PokemonLevel):-
		(  H =< PokemonLevel
        -> true
        ;  false
    	).
	
	% this predicate is designed to assign EvolvedPokemonTemp to EvolvedPokemon. 
	% Since the "is" opperator does not work in any conditon except for matematical funtions so we determine EvolvedPokemonTemp
	% and assign it to EvolvedPokemon.
	% esislee(-EvolvedPokemon,+EvolvedPokemonTemp).
	  esislee(EvolvedPokemon,EvolvedPokemonTemp):-
	  pokemon_stats(EvolvedPokemonTemp,_,Healthfln,AtatckFln,Budefkanki),pokemon_stats(EvolvedPokemon,_,Healthfln,AtatckFln,Budefkanki).	


	% this predicate is designed to find the needed information of the pokemon. I use pokemon_stats() predicate that is already designed and 
	% determine the PokemonHp, PokemonAttack,PokemonDefense  as is required in PDF.
	% pokemon_level_stats(+PokemonLevel, ?Pokemon, -PokemonHp, -PokemonAttack,-PokemonDefense).
	  pokemon_level_stats(PokemonLevel, Pokemon, PokemonHp, PokemonAttack,PokemonDefense):-
	  pokemon_stats(Pokemon,_,K,L,M),(PokemonHp is K+2*PokemonLevel),(PokemonAttack is L+PokemonLevel),(PokemonDefense is M+PokemonLevel).

	
	% this predicate is designed to find the Multiplier because every pokemon has advantages and disadvantages to each other. In this predicate I determine the Pokemon_attack_List by
	% using type_chart_attack() and Pokemon_def_List by using pokemon_types() and pass them into  single_type_multiplier2.
	% single_type_multiplier(?AttackerType, +DefenderType, ?Multiplier).
	  single_type_multiplier(AttackerType, DefenderType, Multiplier):-
      	  type_chart_attack(AttackerType,Pokemon_attack_List),pokemon_types(Pokemon_def_List),single_type_multiplier2(AttackerType,DefenderType,Multiplier,Pokemon_attack_List,Pokemon_def_List).
	
	% this predicate is designed to assist single_type_multiplier. I check every iteretion 
	% if Multiplier and DefenderType are equal to the elements of Pokemon_attack_List and Pokemon_def_List lists.
	% single_type_multiplier2(?AttackerType, +DefenderType, ?Multiplier,[+H|+Pokemon_attack_List_Tail],[+M|+Pokemon_def_List_Tail]).
	  single_type_multiplier2(AttackerType,DefenderType,Multiplier,[H|Pokemon_attack_List_Tail],[M|Pokemon_def_List_Tail]):-
	  ((M=DefenderType),(Multiplier=H),!);single_type_multiplier2(AttackerType,DefenderType,Multiplier,Pokemon_attack_List_Tail,Pokemon_def_List_Tail).


	

	

	% this predicate is designed to multiplied. I may have AttackerType and DefenderTypeList.I create type_multiplier2 as an assistant and pass the DefenderTypeList.
	% type_multiplier(?AttackerType, +DefenderTypeList, ?Multiplier).
	  type_multiplier(AttackerType, [H|DefenderTypeListTail], Multiplier):-
	  type_multiplier2(AttackerType, [H|DefenderTypeListTail],Multiplier).

	% this predicate is designed to assist type_multiplier. I have the beginning element of DefenderTypeList that I called H and by using single_type_multiplier predicate and H
	% I calculated MultiplierTemp and sent it into type_multiplier3 so that there is no error in multipling.
	% type_multiplier2(?AttackerType, [+H|+DefenderTypeListTail],?Multiplier).
	  type_multiplier2(AttackerType, [H|DefenderTypeListTail],Multiplier):-
	  single_type_multiplier(AttackerType, H, MultiplierTemp),type_multiplier3(AttackerType, DefenderTypeListTail, MultiplierTemp,Multiplier).

	% Now, I have a value different from 0 and by using single_type_multiplier I calculated the rest of the DefenderTypeList. 
	% type_multiplier3(?AttackerType, +[H|DefenderTypeListTail], ?Multiplier3,?Multiplier).
	  type_multiplier3(AttackerType, [H|DefenderTypeListTail], MultiplierT3,Multiplier):-
	  single_type_multiplier(AttackerType, H, MultiplierTemps),(AnewMultiplier is MultiplierTemps*MultiplierT3),type_multiplier3(AttackerType, DefenderTypeListTail, AnewMultiplier,Multiplier).
	% When DefenderTypeList is empty I assign the value to Multiplier. 
	  type_multiplier3(_, [],AnewMultiplier,Multiplier):-(Multiplier is (AnewMultiplier+0)).
    


   

	
	% this predicate is designed to calculate the Multiplier that the AttackerPokemon has against DefenderPokemon.
	% First, I use pokemon_stats predicate to take AttackerPokemonTypeList and DefenderPokemonTypeList after that pass them to pokemon_type_multiplier2.
	% pokemon_type_multiplier(?AttackerPokemon, ?DefenderPokemon, ?Multiplier).
      pokemon_type_multiplier(AttackerPokemon,DefenderPokemon,Multiplier):-
      pokemon_stats(AttackerPokemon,AttackerPokemonTypeList,_,_,_),pokemon_stats(DefenderPokemon,DefenderPokemonTypeList,_,_,_),
      pokemon_type_multiplier2(AttackerPokemonTypeList,DefenderPokemonTypeList,Multiplier,0).

	% this predicate is designed to assist pokemon_type_multiplier. By using type_multiplier and the beginning of the AttackerPokemonTypeList I call H , I callculated the a value
	% and if the value is higher then the Base then I pass the next pokemon_type_multiplier2 the new value if it is not so then I pass the Base value unchanged.
	% pokemon_type_multiplier2(?[H|AttackerPokemonTypeListTail], ?DefenderPokemonTypeList,?Multiplier,?Base).
	  pokemon_type_multiplier2([H|AttackerPokemonTypeListTail], DefenderPokemonTypeList,Multiplier,Base):-
      type_multiplier(H,DefenderPokemonTypeList,Musti),
      (Musti > Base 
      -> pokemon_type_multiplier2(AttackerPokemonTypeListTail,DefenderPokemonTypeList,Multiplier,Musti)
      ;
      pokemon_type_multiplier2(AttackerPokemonTypeListTail,DefenderPokemonTypeList,Multiplier,Base)).
     
      % when we have empty AttackerPokemonTypeList I assign the final callculated value to Multiplier.
      pokemon_type_multiplier2([],_,Multiplier,Base):-   (Multiplier is Base).

   

	% this predicate is designed to calculate the damage by considering the level of Pokemons.
	% pokemon_attack(+AttackerPokemon, +AttackerPokemonLevel, +DefenderPokemon,+DefenderPokemonLevel, -Damage).
      pokemon_attack(AttackerPokemon, AttackerPokemonLevel, DefenderPokemon,DefenderPokemonLevel, Damage):-
      pokemon_level_stats(AttackerPokemonLevel, AttackerPokemon, _, AttackerPokemonAttack, _),
      pokemon_level_stats(DefenderPokemonLevel, DefenderPokemon, _, _, DefenderPokemonDefense),
      pokemon_type_multiplier(AttackerPokemon,DefenderPokemon,TypeMultiplier),(Damage is ((0.5*AttackerPokemonLevel*(AttackerPokemonAttack/DefenderPokemonDefense)*TypeMultiplier)+1)).
 

	% this predicate is designed to find the winner pokemon after fight. In this predicate I create another predicate and pass 0 value as RoundsToAssign that will be calculated in pokemon_fight2.
 	% pokemon_fight(+Pokemon1, +Pokemon1Level, +Pokemon2, +Pokemon2Level,-Pokemon1Hp, -Pokemon2Hp, -Rounds).
 	  pokemon_fight(Pokemon1,Pokemon1Level,Pokemon2,Pokemon2Level,Pokemon1Hp, Pokemon2Hp, Rounds):-
      pokemon_fight2(Pokemon1,Pokemon1Level,Pokemon2,Pokemon2Level,Pokemon1Hp, Pokemon2Hp, Rounds,0).

       % this predicate is designed to assist pokemon_fight.By using pokemon_attack I find the damages of Pokemons and pass them with the other atoms to pokemon_fight3
       % pokemon_fight2(+Pokemon1,+Pokemon1Level,+Pokemon2,+Pokemon2Level,-Pokemon1Hp,-Pokemon2Hp,-Rounds,+RoundsToAssign):-
         pokemon_fight2(Pokemon1,Pokemon1Level,Pokemon2,Pokemon2Level,Pokemon1Hp, Pokemon2Hp, Rounds,RoundsToAssign):-
         pokemon_attack(Pokemon1, Pokemon1Level, Pokemon2,Pokemon2Level, DamageForAttacker1),
         pokemon_attack(Pokemon2, Pokemon2Level, Pokemon1,Pokemon1Level, DamageForAttacker2), 
         pokemon_level_stats(Pokemon1Level, Pokemon1, Pokemon1Health, _, _),
         pokemon_level_stats(Pokemon2Level, Pokemon2, Pokemon2Health, _, _),
         pokemon_fight3(Pokemon1Health,Pokemon2Health,DamageForAttacker1,DamageForAttacker2,Pokemon1Hp,Pokemon2Hp,Rounds,RoundsToAssign).

        % this predicate is designed to assist pokemon_fight2.By using damages I calculated healths of each pokemon left and increase rounds and
	% if the one of them is equal to zero or below pass the all values to pokemon_fight4.
  	% pokemon_attack3(+Pokemon1Health,+Pokemon2Health,+DamageForAttacker1,+DamageForAttacker2,-Pokemon1Hp,-Pokemon2Hp,-Rounds,?RoundsToAssign).
  	  pokemon_fight3(Pokemon1Health,Pokemon2Health,DamageForAttacker1,DamageForAttacker2,Pokemon1Hp,Pokemon2Hp,Rounds,RoundsToAssign):-
 	  (RoundsTemp is (RoundsToAssign+1)),(Pokemon1HealthTemp is (Pokemon1Health-DamageForAttacker2)),(Pokemon2HealthTemp is (Pokemon2Health-DamageForAttacker1)),
 	  (((Pokemon1HealthTemp=<0);(Pokemon2HealthTemp=<0))
 	  -> pokemon_fight4(Pokemon1HealthTemp,Pokemon2HealthTemp,Pokemon1Hp,Pokemon2Hp,Rounds,RoundsTemp)
 	  ;pokemon_fight3(Pokemon1HealthTemp,Pokemon2HealthTemp,DamageForAttacker1,
 	  DamageForAttacker2,Pokemon1Hp,Pokemon2Hp,Rounds,RoundsTemp)).
 	% if the health of any pokemon is equal to zero or below we assign the calculated values to Pokemon1Hp,Pokemon2Hp and Rounds
 	% pokemon_fight4(+Pokemon1HealthTemp,+Pokemon1HealthTemp,-Pokemon1Hp,-Pokemon1Hp,-Rounds,+RoundsToAssign):-
      pokemon_fight4(Pokemon1HealthTemp,Pokemon2HealthTemp,Pokemon1Hp,Pokemon2Hp,Rounds,RoundsToAssign):-
      (Pokemon1Hp is Pokemon1HealthTemp),	
      (Pokemon2Hp is Pokemon2HealthTemp),
 	  (Rounds is RoundsToAssign).


	% this predicate is designed to organize a tournament and determine the WinnerTrainerList.In this predicate I use pokemon_trainer predicate to take the pokemons of each pokemon trainer and their levels
	% and I create extra atoms like WinnerTrainerListToAssignnew and WinnerTrainerListToAssigold and pass them to pokemon_tournament2
 	% pokemon_tournament(+PokemonTrainer1, +PokemonTrainer2, -WinnerTrainerList).
      pokemon_tournament(PokemonTrainer1, PokemonTrainer2, WinnerTrainerList):-
      pokemon_trainer(PokemonTrainer1,PokemonTrainer1ThePokemonList,PokemonTrainer1ThePokemonLevelList),
      pokemon_trainer(PokemonTrainer2,PokemonTrainer2ThePokemonList,PokemonTrainer2ThePokemonLevelList),
      pokemon_tournament2(PokemonTrainer1,PokemonTrainer1ThePokemonList,PokemonTrainer1ThePokemonLevelList,
         	              PokemonTrainer2,PokemonTrainer2ThePokemonList,PokemonTrainer2ThePokemonLevelList,_,_,WinnerTrainerList),!.

        % this predicate is designed to assist pokemon_tournament and we calculate the winnerlist here.I first find the evolved pokemon by using find_pokemon_evolution and 
	% revoke pokemon_fight to find the health values after a fight and if the pokemon of PokemonTrainer1 is the winner I add PokemonTrainer1 into WinnerTrainerListToAssignnew
	% if the reverse sitiation is true then I add the PokemonTrainer1 into WinnerTrainerListToAssignnew. After all I pass WinnerTrainerListToAssignnew into pokemon_tournament2 as
	% a WinnerTrainerListToAssignold one since the next itretion WinnerTrainerListToAssignnew will be changed as the new pokemon trainer is added.		
        % pokemon_tournament2(+PokemonTrainer1,?[H|PokemonTrainer1ThePokemonListTail],?[HLevel|PokemonTrainer1ThePokemonLevelListTail],
        %     	          +PokemonTrainer2,?[K|PokemonTrainer2ThePokemonListTail],?[KLevel|PokemonTrainer2ThePokemonLevelListTail],-WinnerTrainerListToAssignold,-WinnerTrainerListToAssignnew,-WinnerTrainerList).
	  pokemon_tournament2(PokemonTrainer1,[H|PokemonTrainer1ThePokemonListTail],[HLevel|PokemonTrainer1ThePokemonLevelListTail],
	                      PokemonTrainer2,[K|PokemonTrainer2ThePokemonListTail],[KLevel|PokemonTrainer2ThePokemonLevelListTail],WinnerTrainerListToAssignold,WinnerTrainerListToAssignnew,
	                      WinnerTrainerList):-
	  find_pokemon_evolution(HLevel, H, EvolvedH),	find_pokemon_evolution(KLevel, K, EvolvedK),

	  pokemon_fight(EvolvedH,HLevel,EvolvedK,KLevel,PokemonHHp, PokemonKHp, _),
	  (
	 	(PokemonHHp > PokemonKHp) -> append(WinnerTrainerListToAssignold,[PokemonTrainer1],WinnerTrainerListToAssignnew)
	 		;
	 	(PokemonKHp > PokemonHHp) -> append(WinnerTrainerListToAssignold,[PokemonTrainer2],WinnerTrainerListToAssignnew)
	 		;
		(PokemonKHp = PokemonHHp) -> append(WinnerTrainerListToAssignold,[PokemonTrainer1],WinnerTrainerListToAssignnew)

	  ),pokemon_tournament2(PokemonTrainer1,PokemonTrainer1ThePokemonListTail,PokemonTrainer1ThePokemonLevelListTail,
	                        PokemonTrainer2,PokemonTrainer2ThePokemonListTail,PokemonTrainer2ThePokemonLevelListTail,WinnerTrainerListToAssignnew,_,
	                        WinnerTrainerList),!.

	% when we have empty list like level or pokemon I assign the WinnerTrainerListToAssign list into WinnerTrainerList.
	% Actually WinnerTrainerListToAssign is WinnerTrainerListToAssignold but I changed its name to make it look well
	  pokemon_tournament2(_,[],[],_,[],[],WinnerTrainerListToAssign,_,WinnerTrainerList):- append([],WinnerTrainerListToAssign,WinnerTrainerList),!.
	 




	% I determine the the best pokemon against the EnemyPokemon given to me.In this predicate pokemon does not evolve even if they can.
	% I create a PokemonList by using findall and extra atoms called BestPokemonToAssign RemainingHPToAssign and after all sent them into best_pokemon2
 	% best_pokemon(+EnemyPokemon, +LevelCap, -RemainingHP, -BestPokemon).

	  best_pokemon(EnemyPokemon, LevelCap, RemainingHP, BestPokemon):-
	  findall(Pokemon,pokemon_stats(Pokemon, _,_,_,_),PokemonList),
	  best_pokemon2(PokemonList,0,RemainingHP,_,BestPokemon,LevelCap,EnemyPokemon).

	% this predicate is designed to assist best_pokemon. I the first element of PokemonList and make it fight against EnemyPokemon by using pokemon_fight predicate and calculate the PokemonHHp.
	% each iteration I check PokemonHHp condition.If its value is higher then the RemainingHPToAssign then I pass PokemonHHp as a RemainingHPToAssign and pass H pokemon as a BestPokemonToAssign 
	% if it not so then I passed RemainingHPToAssign into best_pokemon2 predicate for the next itreation.
	% best_pokemon2(+PokemonList,+RemainingHPToAssign,-RemainingHP,?BestPokemonToAssign,-BestPokemon,+LevelCap,+EnemyPokemon):-
	  best_pokemon2([H|PokemonListTail],RemainingHPToAssign,RemainingHP,BestPokemonToAssign,BestPokemon,LevelCap,EnemyPokemon):-
	  pokemon_fight(H,LevelCap,EnemyPokemon,LevelCap,PokemonHHp,_,_),
	  (
	 	(PokemonHHp > RemainingHPToAssign)
	 	-> best_pokemon2(PokemonListTail,PokemonHHp,RemainingHP,H,BestPokemon,LevelCap,EnemyPokemon)
	 	;
	 	(PokemonHHp =< RemainingHPToAssign)
	 	-> best_pokemon2(PokemonListTail,RemainingHPToAssign,RemainingHP,BestPokemonToAssign,BestPokemon,LevelCap,EnemyPokemon)

	  ).
	% if the pokemonlist is empty I assign RemainingHPToAssign into RemainingHP and find the BestPokemon by using esislee predicate and BestPokemonToAssign
	  best_pokemon2([],RemainingHPToAssign,RemainingHP,BestPokemonToAssign,BestPokemon,_,_):-
	  (RemainingHP is RemainingHPToAssign),esislee(BestPokemon,BestPokemonToAssign).

	% this predicate is similar to best_pokemon but in this predicate the EnemyPokemon has to be evolved before the fight so I check if it is sufficient to evolved if it is so 
	% I find the evolved EnemyPokemon and send it into best_pokemon2x
	% best_pokemonx(+EnemyPokemon, +LevelCap, -RemainingHP, -BestPokemon).

	  best_pokemonx(EnemyPokemon, LevelCap, RemainingHP, BestPokemon):-
	  findall(Pokemon,pokemon_stats(Pokemon, _,_,_,_),PokemonList),find_pokemon_evolution(LevelCap, EnemyPokemon, EvolvedEnemyPokemon),
	  best_pokemon2x(PokemonList,0,RemainingHP,_,BestPokemon,LevelCap,EvolvedEnemyPokemon).

	% this predicate is the same as best_pokemon2 but I find the the evolved version of H which is the beginning element of PokemonList
	% best_pokemon2x(+[H|PokemonListTail],+RemainingHPToAssign,-RemainingHP,?BestPokemonToAssign,-BestPokemon,+LevelCap,+EvolvedEnemyPokemon):-
	  best_pokemon2x([H|PokemonListTail],RemainingHPToAssign,RemainingHP,BestPokemonToAssign,BestPokemon,LevelCap,EvolvedEnemyPokemon):-
	  find_pokemon_evolution(LevelCap, H, EvolvedH),	
	  pokemon_fight(EvolvedH,LevelCap,EvolvedEnemyPokemon,LevelCap,PokemonHHp,_,_),
	  (
	 	(PokemonHHp > RemainingHPToAssign)
	 	-> best_pokemon2x(PokemonListTail,PokemonHHp,RemainingHP,EvolvedH,BestPokemon,LevelCap,EvolvedEnemyPokemon)
	 	;
	 	(PokemonHHp =< RemainingHPToAssign)
	 	-> best_pokemon2x(PokemonListTail,RemainingHPToAssign,RemainingHP,BestPokemonToAssign,BestPokemon,LevelCap,EvolvedEnemyPokemon)

	  ).
	% if the pokemonlist is empty I assign RemainingHPToAssign into RemainingHP and find the BestPokemon by using esislee predicate and BestPokemonToAssign
	  best_pokemon2x([],RemainingHPToAssign,RemainingHP,BestPokemonToAssign,BestPokemon,_,_):-
	  (RemainingHP is RemainingHPToAssign),esislee(BestPokemon,BestPokemonToAssign).





	% this predicate is design to find the Pokemon team which has the best condition like types.
	% By using pokemon_trainer predicate I find the OpponentTrainerThePokemonList and OpponentTrainerThePokemonLevelList.I create extra atoms called PokemonTeamOld and PokemonTeamNew
	% and send them into best_pokemon_team2 predicate
	% best_pokemon_team(+OpponentTrainer, -PokemonTeam)
	  best_pokemon_team(OpponentTrainer, PokemonTeam):-
	  pokemon_trainer(OpponentTrainer,OpponentTrainerThePokemonList,OpponentTrainerThePokemonLevelList),
	  best_pokemon_team2(OpponentTrainerThePokemonList,OpponentTrainerThePokemonLevelList,_,_,PokemonTeam),!.

	% this predicate is design to assist best_pokemon_team. I take the first element of OpponentTrainerThePokemonList called H and OpponentTrainerThePokemonLevelList called K.
	% I send them into best_pokemonx because I want the best pokemon aginst H as an evolved and append it into  PokemonTeamNew and sent the next iteration as a PokemonTeamOld 
	% best_pokemon_team2(+[H|OpponentTrainerThePokemonListTail],+[K|OpponentTrainerThePokemonLevelListTail],-PokemonTeamOld,-PokemonTeamNew,-PokemonTeam):-
	  best_pokemon_team2([H|OpponentTrainerThePokemonListTail],[K|OpponentTrainerThePokemonLevelListTail],PokemonTeamOld,PokemonTeamNew,PokemonTeam):-
	  best_pokemonx(H, K ,_, BestPokemon),append(PokemonTeamOld,[BestPokemon],PokemonTeamNew),
	  best_pokemon_team2(OpponentTrainerThePokemonListTail,OpponentTrainerThePokemonLevelListTail,PokemonTeamNew,_,PokemonTeam),!.

	% when we have empty OpponentTrainerThePokemonList and OpponentTrainerThePokemonLevelList I assign the last prepared PokemonTeamNew list to PokemonTeam
	  best_pokemon_team2([],[],PokemonTeamNew,_,PokemonTeam):-append([],PokemonTeamNew,PokemonTeam),!.


	% this predicate is design to find PokemonList that every pokemon is both member of InitialPokemonList and its type is the member of TypeList.I find if the pokemon is the member of 
	% InitialPokemonList or not in this predicate but I find its type condition in pokemon_types_2. I used findall predicate to create PokemonList
	% pokemon_types(+TypeList, +InitialPokemonList, -PokemonList).	
	  pokemon_types(TypeList,InitialPokemonList,PokemonList):-
	  findall(Pokemon,(member(Pokemon,InitialPokemonList),pokemon_types_2(TypeList,Pokemon)),PokemonList).

	% this predicate is design to assist pokemon_types predicate and I take the first element of TypeList and called it H and I check whether it is the member of the PokemonTypeList
	% after I found it by using  pokemon_stats predicate. If it is so then I stop but if it is not so then I need to go to next iteration.
 	% pokemon_types_2([?H|?TypeListTail], ?Pokemon).
		
	  pokemon_types_2([H|TypeListTail],Pokemon):-
	  pokemon_stats(Pokemon,PokemonTypeList,_,_,_),
	  ((member(H,PokemonTypeList),!);pokemon_types_2(TypeListTail,Pokemon)).
	
	% this predicate is simililar to pokemon_types_2 but I dont stop if the first element of TypeList is the member of the PokemonTypeList because I need all of them like I have 
	% TypeList such as [dragon] and ı need to find the all pokemon that their types are the member of this TypeList so I do not use cut
	% pokemon_types_3([?H|?TypeListTail], ?Pokemon).
	  pokemon_types_3([H|TypeListTail],Pokemon):-
	  pokemon_stats(Pokemon,PokemonTypeList,_,_,_),
	  ((member(H,PokemonTypeList));pokemon_types_3(TypeListTail,Pokemon)).

	 


		
	% this predicate is design to find the PokemonTeamList by considering given Criterion,LikedTypes and DislikedTypes. PokemonTeamList is a list of list.its element are actually a list composed of
	% Pokemonname,HealthBar,AttackNumber,and DefNumber.I find all of them by using pokemon_stats inside of findall predicate ehich is to create PokemonList.
	% The pokemon type has to be member of LikedTypes and do not to be the member of DislikedTypes  so I used \+ as a not operator we are accustom to.
	% After all I pass the PokemonList, Criterion, Count and PokemonTeam to generate_pokemon_team2.
	% generate_pokemon_team(+LikedTypes, +DislikedTypes, +Criterion, +Count,-PokemonTeam).
	  generate_pokemon_team(LikedTypes, DislikedTypes, Criterion, Count,PokemonTeam):-
          findall([Pokemon,HealthBar,AttackNumber,DefNumber],(pokemon_types_3(LikedTypes,Pokemon),\+pokemon_types_3(DislikedTypes,Pokemon),
	  pokemon_stats(Pokemon,_,HealthBar,AttackNumber,DefNumber)),PokemonList),
	  generate_pokemon_team2(PokemonList,Criterion,Count,PokemonTeam).
	
	% this predicate is design to assist generate_pokemon_team.In this predicate I add a value according to Criterion given to me.If it is h I added the health value of the pokemon into the list
	% that the pokemon is inside of like -HealthBar-Pokemon,HealthBar,AttackNumber,DefNumber. I used the negative sign because after adding I sort them by using keysort and keysort sorts them
	% from min to max. After sorting I take the added values and take the number of elements by considering Count  number.
        % generate_pokemon_team2(+PokemonList,+Criterion,+Count,-PokemonTeam):-
	  generate_pokemon_team2(PokemonList,Criterion,Count,PokemonTeam):-
		(
			(Criterion =h)	->(maplist(findh,PokemonList,PairedPokemonList))
			;
			(Criterion = a)	->(maplist(finda,PokemonList,PairedPokemonList))
			;
			(Criterion = d)	->(maplist(findd,PokemonList,PairedPokemonList))

		),keysort(PairedPokemonList, PairedPokemonListToAssign),pairs_values(PairedPokemonListToAssign,PairedPokemonListToAssign2),
		  take(PairedPokemonListToAssign2,Count,PokemonTeam).
	% this predicate is design to add the Health value 
        %   findh(+PokemonProperties,+HealthBar-PokemonProperties)
		findh(PokemonProperties,HealthBar-PokemonProperties):-find2h(PokemonProperties,HealthBar).
		find2h([Pokemon,_,_,_],HealthBar):-pokemon_stats(Pokemon,_,HealthBarx,_,_),(HealthBar is -HealthBarx).
	% this predicate is design to add the Attack value 
	%	finda(+PokemonProperties,+AttackNumber-PokemonProperties)
		finda(PokemonProperties,AttackNumber-PokemonProperties):-find2a(PokemonProperties,AttackNumber).
		find2a([Pokemon,_,_,_],AttackNumber):-pokemon_stats(Pokemon,_,_,AttackNumberx,_),(AttackNumber is -AttackNumberx).
	% this predicate is design to add the Defends value 
	%   findd(+PokemonProperties,+DefNumber-PokemonProperties)
		findd(PokemonProperties,DefNumber-PokemonProperties):-find2d(PokemonProperties,DefNumber).
		find2d([Pokemon,_,_,_],DefNumber):-pokemon_stats(Pokemon,_,_,_,DefNumberx),(DefNumber is -DefNumberx).
		
	% this predicate is design to take the added values away from the element
 	%   pairs_values([_?-V|?T0], [?V|?T]) :-
        pairs_values([], []).
        pairs_values([_-V|T0], [V|T]) :-
        pairs_values(T0, T).

	% this predicate is design to take the first number of elements of the lists and add them to PokemonTeam.	
	%	take(+Src,+N,-L)
   	    take(Src,N,L) :- findall(E, (nth1(I,Src,E), I =< N), L).
 












