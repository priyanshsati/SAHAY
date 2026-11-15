use sahay;

set foreign_key_checks = 0;
truncate table rescue_team_members;
truncate table rescue_teams;
truncate table people;
truncate table households;
truncate table hospitals;
truncate table shelters;
truncate table disasters;
truncate table road_conditions;
truncate table roads;
truncate table locations;
set foreign_key_checks = 1;

-- locations
insert into locations (id, name, type, latitude, longitude, population) values
(1, 'Clock Tower (City Center)', 'Urban', 30.325564, 78.043682, 45000),
(2, 'ISBT Dehradun', 'Highway Junction', 30.2862, 78.0081, 32000),
(3, 'Premnagar', 'Town', 30.3344, 77.9622, 28000),
(4, 'Raipur', 'Town', 30.309, 78.087, 26000),
(5, 'Badowala', 'Village / Rural', 30.298, 77.942, 8500),
(6, 'Rajpur Road', 'Urban / Foothill', 30.368, 78.068, 22000),
(7, 'Mussoorie', 'Hilly / Mountain Town', 30.4598, 78.0644, 30000),
(8, 'Sahastradhara', 'River Valley / Hill', 30.384, 78.131, 9200),
(9, 'Maldevta', 'River Valley / Flood-prone', 30.321, 78.14, 7400),
(10, 'Clement Town', 'Town / Plains', 30.267, 78.016, 21000),
(11, 'Doiwala', 'Town / Plains', 30.179, 78.121, 19500),
(12, 'Rishikesh', 'Town / River Border', 30.0869, 78.2676, 48000),
(13, 'Jhajra', 'Suburban', 30.342, 77.925, 11000),
(14, 'Selaqui', 'Industrial / Plains', 30.365, 77.854, 25000),
(15, 'Vikas Nagar (Herbertpur)', 'Town / Western Plains', 30.432, 77.728, 35000);

-- roads
insert into roads (id, from_id, to_id, distance, road_type, is_one_way) values
(1, 1, 2, 6.2, 'Arterial', 0),
(2, 1, 3, 9.5, 'National Highway', 0),
(3, 1, 4, 5.8, 'Arterial', 0),
(4, 1, 6, 7.1, 'Arterial', 0),
(5, 2, 5, 8.4, 'State Highway', 0),
(6, 2, 10, 4.2, 'National Highway', 0),
(7, 2, 3, 8.1, 'State Highway', 0),
(8, 3, 5, 5.1, 'Village Road', 0),
(9, 3, 13, 4.3, 'National Highway', 0),
(10, 3, 6, 12.8, 'Arterial', 0),
(11, 4, 8, 9.2, 'State Highway', 0),
(12, 4, 9, 7.5, 'River Valley Road', 0),
(13, 4, 11, 14.2, 'State Highway', 0),
(14, 5, 13, 6.0, 'Village Road', 0),
(15, 5, 10, 9.8, 'State Highway', 0),
(16, 6, 7, 24.5, 'Hilly Road', 0),
(17, 6, 8, 8.7, 'Hilly Road', 0),
(18, 7, 8, 26.0, 'Hilly Road', 0),
(19, 8, 9, 8.1, 'River Valley Road', 0),
(20, 9, 11, 15.6, 'River Valley Road', 0),
(21, 10, 11, 16.4, 'National Highway', 0),
(22, 11, 12, 21.0, 'National Highway', 0),
(23, 4, 12, 36.5, 'State Highway', 0),
(24, 13, 14, 7.8, 'National Highway', 0),
(25, 14, 15, 16.5, 'National Highway', 0),
(26, 5, 14, 11.2, 'Village Road', 0);

-- road conditions
insert into road_conditions (road_id, water_level, traffic, flood_severity, landslide_risk, road_damage, blocked) values
(1, 0.0, 30, 0, 0, 10, 0),
(2, 0.0, 40, 0, 0, 15, 0),
(3, 0.0, 25, 0, 0, 5, 0),
(4, 0.0, 35, 0, 10, 10, 0),
(5, 0.0, 20, 0, 0, 10, 0),
(6, 0.0, 45, 0, 0, 10, 0),
(7, 0.0, 20, 0, 0, 10, 0),
(8, 0.0, 10, 0, 0, 5, 0),
(9, 0.0, 25, 0, 0, 5, 0),
(10, 0.0, 30, 0, 0, 10, 0),
(11, 0.1, 20, 15, 20, 15, 0),
(12, 0.6, 10, 75, 40, 60, 0),
(13, 0.0, 15, 5, 10, 10, 0),
(14, 0.0, 10, 0, 0, 5, 0),
(15, 0.0, 20, 0, 0, 10, 0),
(16, 0.0, 30, 0, 65, 30, 0),
(17, 0.0, 15, 0, 20, 10, 0),
(18, 0.0, 10, 0, 85, 50, 0),
(19, 0.4, 5, 60, 40, 45, 0),
(20, 0.3, 10, 40, 20, 20, 0),
(21, 0.0, 40, 0, 0, 10, 0),
(22, 0.0, 35, 0, 0, 5, 0),
(23, 0.0, 15, 10, 10, 10, 0),
(24, 0.0, 25, 0, 0, 5, 0),
(25, 0.0, 20, 0, 0, 5, 0),
(26, 0.0, 10, 0, 0, 10, 0);

-- hospitals
insert into hospitals (id, location_id, name, available_beds, contact) values
(1, 1, 'Doon Government Medical College & Hospital', 180, '+91-135-2726020'),
(2, 6, 'Max Super Speciality Hospital, Rajpur', 95, '+91-135-7193000'),
(3, 3, 'Combined Medical Institute (CMI) Premnagar', 45, '+91-135-2771234'),
(4, 10, 'Graphic Era Institute of Medical Sciences', 120, '+91-135-2642727'),
(5, 12, 'AIIMS Rishikesh', 260, '+91-135-2462929'),
(6, 11, 'Community Health Centre (CHC) Doiwala', 30, '+91-135-2695123'),
(7, 15, 'Sub-District Hospital Vikas Nagar', 50, '+91-135-2522100');

-- shelters
insert into shelters (id, location_id, name, capacity, occupied) values
(1, 1, 'Pavilion Ground Indoor Hall, Dehradun', 600, 120),
(2, 2, 'ISBT Community Relief Centre', 400, 80),
(3, 3, 'Premnagar Cantonment Community Shelter', 350, 50),
(4, 4, 'Raipur Sports Stadium Evacuation Camp', 800, 210),
(5, 5, 'Badowala Panchayat Bhawan Shelter', 180, 30),
(6, 11, 'Doiwala Sugar Mill Ground Shelter', 450, 90),
(7, 12, 'Rishikesh Bharat Mandir Relief Centre', 500, 150),
(8, 14, 'Selaqui Industrial Welfare Center', 300, 40);

-- rescue teams
insert into rescue_teams (id, name, team_type, current_location_id, available) values
(1, 'Alpha SDRF Unit', 'SDRF (State Disaster Response)', 1, 1),
(2, 'Bravo Flood Rescue', 'NDRF Riverine & Flood Rescue', 4, 1),
(3, 'Charlie Mountain Corps', 'Mountain & Landslide SAR', 6, 1),
(4, 'Delta Medical Quick-Evac', 'Medical Emergency Evacuation', 2, 1),
(5, 'Echo Rural Rescue', 'Civil Defense / Fire Rescue', 3, 1);

-- rescue team members
insert into rescue_team_members (id, rescue_team_id, member_name, role) values
(1, 1, 'Priyansh', 'Incident Commander / Lead Coordinator'),
(2, 1, 'Vikas', 'Navigation & Communications Specialist'),
(3, 1, 'Kapil', 'First Responder & Tactical Diver'),
(4, 2, 'Gaje', 'Team Leader - Aquatic SAR'),
(5, 2, 'Lovkesh', 'Powerboat Operator & Diver'),
(6, 2, 'Shailesh', 'Medical Trauma Specialist'),
(7, 3, 'Robin', 'High-Angle Mountain Rescue Leader'),
(8, 3, 'Deva', 'Rope Rigging & Evacuation Specialist'),
(9, 3, 'Tanish', 'Heavy Machinery & Debris Clearance'),
(10, 4, 'Sandeep', 'Paramedic Lead Officer'),
(11, 4, 'Nitin', 'Field Ambulance Driver & Medic'),
(12, 5, 'Sahil', 'Civil Defense Coordinator'),
(13, 5, 'Ansh', 'Structural Damage Assessor'),
(14, 5, 'Saurabh', 'Emergency Logistics Officer');

-- households
insert into households (id, location_id, address, members, phone) values
(1, 9, 'H.No 12, Near Song River Bridge, Maldevta', 5, '9876543210'),
(2, 9, 'H.No 34, Riverbed Basti, Maldevta', 4, '9876543211'),
(3, 8, 'H.No 7, Upper Stream Colony, Sahastradhara', 6, '9876543212'),
(4, 5, 'H.No 88, Main Chowk, Badowala', 5, '9876543213'),
(5, 4, 'H.No 102, Shivalik Puram, Raipur', 4, '9876543214'),
(6, 3, 'H.No 15, Near Cantonment Board, Premnagar', 3, '9876543215');

-- people
insert into people (id, household_id, name, age, weak, status) values
(1, 1, 'Ramesh Rawat', 68, 1, 'Safe'),
(2, 1, 'Kamla Rawat', 64, 1, 'Safe'),
(3, 1, 'Anil Rawat', 38, 0, 'Safe'),
(4, 1, 'Sunita Rawat', 35, 0, 'Safe'),
(5, 1, 'Aarav Rawat', 6, 1, 'Safe'),
(6, 2, 'Mahesh Negi', 45, 0, 'Evacuated'),
(7, 2, 'Pooja Negi', 42, 0, 'Evacuated'),
(8, 2, 'Rohan Negi', 17, 0, 'Evacuated'),
(9, 2, 'Geeta Devi', 79, 1, 'Injured'),
(10, 3, 'Kundan Singh', 52, 0, 'Safe'),
(11, 4, 'Baldev Sharma', 71, 1, 'Safe'),
(12, 5, 'Meenakshi Bisht', 29, 0, 'Safe'),
(13, 6, 'Gurpreet Singh', 33, 0, 'Safe');

-- disasters
insert into disasters (id, disaster_type, location_id, severity, description, status) values
(1, 'Flash Flood', 9, 85, 'Flash flood along Song River in Maldevta area following sudden cloudburst upstream. Riverbed road submerged.', 'Active'),
(2, 'Landslide', 8, 65, 'Landslide and scree movement near Sahastradhara sulfur springs blocking shoulder.', 'Active'),
(3, 'Waterlogging', 4, 35, 'Urban waterlogging on Raipur canal road causing heavy traffic delays.', 'Containing');
