select sum(attendance) as 'total attendance' 
from cfb_game_stats;

select distinct R.down, R.totals as 'Penalties' 
from cfb_play,
  (select down, count(down) as totals 
  from cfb_play 
  where play_type = 'PENALTY' 
  group by down
  )R
where R.totals >= ALL(select count(down) as totals 
                      from cfb_play 
                      where play_type = 'PENALTY' 
                      group by down
                      )
;

select distinct cfb_team.name, (A.red_zone_success/B.red_zone_attempts) as rate 
from
  (select team_id, count(team_id) as red_zone_success 
  from cfb_drive 
  where red_zone_attempt = 1 
  and end_reason = 'TOUCHDOWN' 
  group by team_id
  )A, 
  (select team_id, count(team_id) as red_zone_attempts 
  from cfb_drive 
  where red_zone_attempt = 1 
  group by team_id
  )B,
  cfb_team
where A.team_id = B.team_id
and cfb_team.team_id = A.team_id
and B.red_zone_attempts > 10 
order by rate desc, cfb_team.name desc
limit 5;

select distinct D.name, avg(B.duration) as duration
from cfb_team A, cfb_game_stats B, cfb_game C, cfb_conference D 
where C.game_id = B.game_id 
  and (A.team_id = C.visit_team_id or A.team_id = C.home_team_id) 
  and A.conference_id = D.conference_id
group by D.name
order by duration desc
limit 1;

select distinct P.first_name as 'first name', P.last_name as 'last name'
from cfb_player P, 
  (select cfb_rush.player_id, sum(cfb_rush.yards) as yds 
  from cfb_play, cfb_rush, cfb_player, cfb_game 
  where cfb_game.game_id = cfb_play.game_id 
    and cfb_play.game_id = cfb_rush.game_id 
    and cfb_player.player_id = cfb_rush.player_id 
    and cfb_play.play_number = cfb_rush.play_number 
    and month(cfb_game.game_date) = 10 
    and cfb_play.down = 1 
  group by player_id 
  order by yds desc 
  limit 1
  )A
where P.player_id = A.player_id;


select B.homestate, B.cnt, C.total as 'number', B.cnt/C.total as percent 
from
  (select sum(B.cnt) as total 
  from 
    (select count(A.homestate) as cnt 
    from 
      (select distinct cfb_player.player_id, cfb_player.homestate 
      from cfb_player, cfb_team 
      where cfb_player.team_id = cfb_team.team_id 
      and cfb_team.name = 'notre dame'
      )A
    group by A.homestate
    order by cnt
    )B
  )C,
  (select A.homestate, count(A.homestate) as cnt 
  from 
    (select distinct cfb_player.player_id, cfb_player.homestate 
    from cfb_player, cfb_team 
    where cfb_player.team_id = cfb_team.team_id 
    and cfb_team.name = 'notre dame'
    )A
  group by A.homestate
  order by cnt desc
  limit 1
  )B,
  (select distinct cfb_player.player_id, cfb_player.homestate 
  from cfb_player, cfb_team 
  where cfb_player.team_id = cfb_team.team_id 
    and cfb_team.name = 'notre dame'
  )A
limit 1;


select count(A.cnt) as players 
from 
  (select player_id, count(player_id) as cnt 
  from cfb_player 
  group by player_id 
  order by cnt desc
  )A 
where A.cnt >= 3;

select distinct P.first_name as 'first name', P.last_name as 'last name', R.yards, T.name as team, year(G.game_date) as year
from cfb_play A, cfb_player P, cfb_game G, cfb_reception R, cfb_team T
where R.game_id = A.game_id
  and G.game_id = A.game_id
  and A.period = 4
  and R.play_number = A.play_number
  and R.player_id = P.player_id
  and R.team_id = T.team_id
  and P.team_id = T.team_id
  and R.yards >= ALL(select R.yards from cfb_reception R)
order by yards desc;

select cfb_team.name as name, cfb_team.year as year, sum(cfb_game_stats.attendance) as att 
from cfb_team, cfb_game_stats, cfb_game 
where cfb_game_stats.game_id=cfb_game.game_id 
  and cfb_game.home_team_id=cfb_team.team_id 
  and cfb_team.year = year(cfb_game.game_date) 
group by name, year 
order by att desc 
limit 5;
