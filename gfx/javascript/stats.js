class Stats {
	constructor(teamNames) {
		this.teams = teamNames.map(name => ( {
			playersOnTeam: 0,
			highestLevelOnTeam: 1,
			playersAtHighestLevel: 0,
			teamName: name,
			winners: undefined,
		}));
	}

	incPlayerCount(id) {
		this.teams[id].playersOnTeam += 1;
	}


	decPlayerCount(id, level) {
		this.teams[id].playersOnTeam -= 1;
		if (level === this.highestLevelOnTeam) {
			this.teams[id].playersAtHighestLevel -= 1;
		}
	}

	incHighestLevel(level, playerIds) {
		var id = 0;
		for (var i = 0; i < playerIds.length; i++) {
			id = game.get_player(playerIds[i]).team;
			if (level > this.teams[id].highestLevelOnTeam) {
				this.teams[id].highestLevelOnTeam += 1;
				this.teams[id].playersAtHighestLevel = 1;
			}
			else if (level === this.teams[id].highestLevelOnTeam) {
				this.teams[id].playersAtHighestLevel += 1;
			}
		}
	}

	displayWinningTeam(ids) {
		this.winners = ids;
	}

}
