create database sahay;
use sahay;

-- 1. places of the city
create table locations (
    id int primary key auto_increment,
    name varchar(40),
    type varchar(20),
    x float,
    y float
);

-- 2. roads between two places
create table roads (
    id int primary key auto_increment,
    from_id int,
    to_id int,
    distance float,
    foreign key (from_id) references locations(id),
    foreign key (to_id) references locations(id)
);

-- 3. condition of each road (changes during disaster)
create table road_conditions (
    road_id int primary key,
    water_level float,
    traffic int,
    blocked int,
    foreign key (road_id) references roads(id)
);

-- 4. houses
create table households (
    id int primary key auto_increment,
    location_id int,
    address varchar(60),
    members int,
    phone varchar(15),
    foreign key (location_id) references locations(id)
);

-- 5. people living in the houses
create table people (
    id int primary key auto_increment,
    household_id int,
    name varchar(40),
    age int,
    weak int,
    status varchar(20),
    foreign key (household_id) references households(id)
);

-- 6. type of disaster
create table disasters (
    id int primary key auto_increment,
    type varchar(20),
    severity int,
    started_on date,
    status varchar(20)
);

-- 7. place where help is needed
create table incidents (
    id int primary key auto_increment,
    disaster_id int,
    location_id int,
    victims int,
    status varchar(20),
    foreign key (disaster_id) references disasters(id),
    foreign key (location_id) references locations(id)
);

-- 8. rescue teams
create table rescue_teams (
    id int primary key auto_increment,
    name varchar(30),
    type varchar(20),
    capacity int,
    location_id int,
    status varchar(20),
    foreign key (location_id) references locations(id)
);

-- 9. which team goes to which incident (filled when the program runs)
create table assignments (
    id int primary key auto_increment,
    team_id int,
    incident_id int,
    people_rescued int,
    foreign key (team_id) references rescue_teams(id),
    foreign key (incident_id) references incidents(id)
);

-- 10. hospitals
create table hospitals (
    id int primary key auto_increment,
    location_id int,
    name varchar(40),
    total_beds int,
    free_beds int,
    foreign key (location_id) references locations(id)
);

-- 11. relief camps where rescued people stay
create table shelters (
    id int primary key auto_increment,
    location_id int,
    name varchar(40),
    capacity int,
    foreign key (location_id) references locations(id)
);

-- 12. things kept for rescue work
create table supplies (
    id int primary key auto_increment,
    location_id int,
    item varchar(30),
    quantity int,
    foreign key (location_id) references locations(id)
);

-- data
insert into locations (name, type, x, y) values
('Clock Tower', 'base', 0, 0),
('Prem Nagar', 'area', -6, -2),
('ISBT', 'area', 5, -1),
('Bahuwala', 'area', -5, 3),
('Clement Town', 'area', -3, -8),
('Bhaniyawala', 'area', -7, -16),
('Jolly Grant Hospital', 'hospital', 0, -23);

insert into roads (from_id, to_id, distance) values
(1, 2, 7),
(1, 3, 5.5),
(1, 4, 6.5),
(1, 5, 9.5),
(2, 4, 5.5),
(2, 5, 7.5),
(5, 6, 10),
(3, 5, 11.5),
(6, 7, 10.5),
(5, 7, 17.5);

insert into road_conditions (road_id, water_level, traffic, blocked) values
(1, 0, 1, 0),
(2, 0, 4, 0),
(3, 0, 2, 0),
(4, 0, 1, 0),
(5, 1.5, 2, 0),
(6, 0, 0, 1),
(7, 1.2, 1, 0),
(8, 0, 3, 0),
(9, 0, 0, 0),
(10, 0, 1, 0);

insert into households (location_id, address, members, phone) values
(2, 'House 12, Prem Nagar', 3, '9000000001'),
(2, 'House 18, Prem Nagar', 3, '9000000002'),
(4, 'House 5, Bahuwala', 3, '9000000003'),
(5, 'House 9, Clement Town', 4, '9000000004'),
(6, 'House 3, Bhaniyawala', 5, '9000000005');

insert into people (household_id, name, age, weak, status) values
(1, 'Sandeep', 40, 0, 'trapped'),
(1, 'Sunita', 36, 0, 'trapped'),
(1, 'Aarav', 7, 1, 'trapped'),
(2, 'Robin', 45, 0, 'trapped'),
(2, 'Meena', 42, 0, 'trapped'),
(2, 'Kamla', 72, 1, 'trapped'),
(3, 'Vikas', 38, 0, 'trapped'),
(3, 'Pooja', 34, 0, 'trapped'),
(3, 'Riya', 5, 1, 'trapped'),
(4, 'Kapil', 50, 0, 'trapped'),
(4, 'Geeta', 46, 0, 'trapped'),
(4, 'Tanish', 14, 0, 'trapped'),
(4, 'Hari', 78, 1, 'trapped'),
(5, 'Gaje', 44, 0, 'trapped'),
(5, 'Rekha', 40, 0, 'trapped'),
(5, 'Lovkesh', 9, 1, 'trapped'),
(5, 'Shailesh', 70, 1, 'trapped'),
(5, 'Priyansh', 20, 0, 'trapped');

insert into disasters (type, severity, started_on, status) values
('flood', 4, '2026-10-17', 'active'),
('fire', 5, '2026-10-17', 'active');

insert into incidents (disaster_id, location_id, victims, status) values
(1, 6, 5, 'pending'),
(1, 5, 4, 'pending'),
(2, 2, 6, 'pending');

insert into rescue_teams (name, type, capacity, location_id, status) values
('Team Alpha', 'boat', 10, 1, 'free'),
('Team Bravo', 'ambulance', 4, 1, 'free'),
('Team Charlie', 'fire truck', 6, 1, 'free');

insert into hospitals (location_id, name, total_beds, free_beds) values
(7, 'Jolly Grant Hospital', 100, 40);

insert into shelters (location_id, name, capacity) values
(3, 'ISBT Relief Camp', 150),
(4, 'Bahuwala School Shelter', 80);

insert into supplies (location_id, item, quantity) values
(1, 'Life jackets', 50),
(1, 'Food packets', 200),
(1, 'Medical kits', 30),
(1, 'Ropes', 20),
(3, 'Blankets', 100),
(4, 'Drinking water', 150);

-- queries to check the data
select * from locations;

select r.id, a.name, b.name, r.distance, c.water_level, c.traffic, c.blocked
from roads r, locations a, locations b, road_conditions c
where r.from_id = a.id and r.to_id = b.id and r.id = c.road_id;

select l.name, count(p.id) as total_people, sum(p.weak) as weak_people
from locations l, households h, people p
where h.location_id = l.id and p.household_id = h.id
group by l.name;

select i.id, l.name, d.type, d.severity, i.victims
from incidents i, locations l, disasters d
where i.location_id = l.id and i.disaster_id = d.id and i.status = 'pending';
