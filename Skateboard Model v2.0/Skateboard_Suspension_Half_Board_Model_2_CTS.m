% Skateboard Suspension - Half-Board Model 2.0 w/ CTS
% Victoria Rea Vastis
% 2022-09-27
%-------------------------------------------------------------------------

%Variables
md = 0;  % Mass of deck and rider (kg)
mtt = 0; % Mass of skateboard truck top (kg)
mbt = 0; % Mass of skateboard truck bottom (kg)
mc = 0; % Mass of City Trucks suspension (kg)

kc = 0;  % City Trucks spring rate (N/m)
Cc = 0;  % City Trucks damping coefficient (Ns/m)

kbt = 0; % Top bushing spring rate (N/m)
cbt = 0; % Top bushing damping coefficient (Ns/m)

kbb = 0; % Bottom bushing spring rate (N/m)
cbb = 0; % Bottom bushing damping coefficient (Ns/m)

kw = 0;  % Wheel spring rate (N/m)
cw = 0;  % Wheel damping coefficient (Ns/m)

%--------------------------------------------------------------------------

% Main Code
kF3 = (kbt*kbb)/(kbt + kbb);
cF4 = (cbt*cbb)/(cbt + cbb);
