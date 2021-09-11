#Punkty budynku:

building b , antenna a
distance(a,b) <= antenas[a].range

Punktacja s:

s(a, b) = buildings[b].connection_speed * antenas[a].connection_speed - buildings[b].latency * distance(a,b)

max( s(a,b), s)    <- s - list of possible scores

Reward = R - when all buildings are connected
		 0 - otherwise

final_score = sigma_{0<=i<=N} s(i) + Reward
