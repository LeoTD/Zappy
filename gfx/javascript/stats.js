class Stats {
	constructor(teamNames) {
		this.teams = teamNames.map(name => ( {
			playersOnTeam: 0,
			highestLevelOnTeam: 0,
			playersAtHighestLevel: 0,
			teamName: name,
			winners: undefined,
		}));
	}

	incPlayerCount(id) {
		console.log(`inc player count ${this.teams[id].playersOnTeam}`);
		this.teams[id].playersOnTeam += 1;
		console.log(`inc player count ${this.teams[id].playersOnTeam}`);
	}

	decPlayerCount(id, level) {
		console.log(`dec player count ${this.teams[id].playersOnTeam}`);
		this.teams[id].playersOnTeam -= 1;
		console.log(`dec player count ${this.teams[id].playersOnTeam}`);
		if (level === this.highestLevelOnTeam) {
			this.teams[id].playersAtHighestLevel -= 1;
			console.log(`dec highest level count ${this.teams[id].playersAthighestLevel}`);
		}
	}

	incHighestLevel(level, pids) {
		console.log("THIS IS THE LOG", level, pids);
		var id = 0;
		for (var i = 0; i < pids.length; i++) {
			id = game.get_player(pids[i]).team;
			console.log(`curr hlevel: ${this.teams[id].highestLevelOnTeam}`);
			if (level > this.teams[id].highestLevelOnTeam) {
				console.log(`new highest level for team ${id}: ${this.teams[id].highestLevelOnTeam}`);
				this.teams[id].highestLevelOnTeam += 1;
				this.teams[id].playersAtHighestLevel = 1;
			}
			else if (level === this.teams[id].highestLevelOnTeam) {
				this.teams[id].playersAtHighestLevel += 1;
				console.log(`adding to highest level for team ${id}: ${this.teams[id].highestLevelOnTeam} total highest players is ${this.teams[id].playersAtHighestLevel}`);
			}
			else
				console.log("incantation did not affect highest level");
		}
	}

	displayWinningTeam(ids) {
		console.log(this.teamName);
		this.winners = ids;
		console.log(`The winners are: ${ids}`);
	}

}
