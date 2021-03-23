
/*    Question 1    */
select sum(attendance) as 'total attendance' 
from cfb_game_stats;

/*    Question 2    */
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

/*    Question 3    */
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

/*    Question 4    */
select distinct D.name, avg(B.duration) as duration
from cfb_team A, cfb_game_stats B, cfb_game C, cfb_conference D 
where C.game_id = B.game_id 
  and (A.team_id = C.visit_team_id or A.team_id = C.home_team_id) 
  and A.conference_id = D.conference_id
group by D.name
order by duration desc
limit 1;

/*    Question 5    */
select cfb_player.first_name as 'first name', cfb_player.last_name as 'first name' 
from cfb_player, 
  (select D.player_id, sum(D.yards)
  from 
    (select cfb_pass.yards, cfb_pass.passer_player_id as player_id
    from cfb_pass, 
      (select cfb_play.game_id, cfb_play.play_number, cfb_play.down 
        from cfb_play, cfb_game 
        where cfb_play.down = 1 
          and cfb_game.game_id = cfb_play.game_id 
          and month(cfb_game.game_date) = 10
      )A
    where A.play_number = cfb_pass.play_number
      and A.game_id = cfb_pass.game_id 
    union
    select cfb_rush.yards, cfb_rush.player_id
    from cfb_rush, 
      (select cfb_play.game_id, cfb_play.play_number, cfb_play.down 
      from cfb_play, cfb_game 
      where cfb_play.down = 1 
      and cfb_game.game_id = cfb_play.game_id 
      and month(cfb_game.game_date) = 10
      )B
      where B.play_number = cfb_rush.play_number
      and B.game_id = cfb_rush.game_id 
    union
    select cfb_reception.yards, cfb_reception.player_id
    from cfb_reception, 
      (select cfb_play.game_id, cfb_play.play_number, cfb_play.down 
      from cfb_play, cfb_game 
      where cfb_play.down = 1  
        and cfb_game.game_id = cfb_play.game_id 
        and month(cfb_game.game_date) = 10
      )C
    where C.play_number = cfb_reception.play_number
      and C.game_id = cfb_reception.game_id 
    )D
    group by D.player_id 
    order by sum(D.yards) 
    desc limit 1
  )F 
where F.player_id = cfb_player.player_id;


/*    Question 6   */
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


/*    Question 7    */
select count(A.cnt) as players 
from 
  (select player_id, count(player_id) as cnt 
  from cfb_player 
  group by player_id 
  order by cnt desc
  )A 
where A.cnt >= 3;

/*    Question 8    */
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

/*    Question 9    */
select cfb_team.name as name, cfb_team.year as year, sum(cfb_game_stats.attendance) as att 
from cfb_team, cfb_game_stats, cfb_game 
where cfb_game_stats.game_id=cfb_game.game_id 
  and cfb_game.home_team_id=cfb_team.team_id 
  and cfb_team.year = year(cfb_game.game_date) 
group by name, year 
order by att desc 
limit 5;
