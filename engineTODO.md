HELLSPACE PROTOTYPE TODO

========================
PHASE 1 — ENGINE CORE
=====================

[ ] engine_init()
- create window
- set FPS

[ ] engine_running()
- return !WindowShouldClose()

[ ] engine_dt()
- return GetFrameTime()

[ ] engine_begin_draw()
[ ] engine_end_draw()

[ ] engine_begin_3d(camera)
[ ] engine_end_3d()

========================
PHASE 2 — CAMERA
================

[ ] camera_create(position, target)
[ ] camera_update_basic(camera)   // optional

========================
PHASE 3 — DRAW WRAPPERS
=======================

[ ] draw_cube(position, size)
[ ] draw_sphere(position, radius)
[ ] draw_plane(size)              // floor
[ ] draw_line3d(start, end)       // optional

========================
PHASE 4 — ENTITY / WORLD (MINIMAL)
==================================

[ ] define Entity struct
- pos
- vel
- mass
- type (static/dynamic)

[ ] define World struct
- dynamic array (entities)
- count
- capacity

[ ] world_create(initial_capacity)

[ ] world_add_entity()
- realloc when needed

[ ] entity_static(pos, mass)
[ ] entity_dynamic(pos, mass, vel)

========================
PHASE 5 — SIMULATION
====================

[ ] world_update(dt)
- loop all entities
- apply gravity (dynamic only)
- update position

[ ] world_draw()
- draw all entities (sphere or cube)

========================
PHASE 6 — PROTOTYPE TEST (IMPORTANT)
====================================

[ ] create World

[ ] add:
- 1 static entity (sun)
- 1 dynamic entity (player)

[ ] WASD control on dynamic entity (game-side)

[ ] render:
- entities
- plane (floor)

[ ] verify:
- movement works
- gravity works
- camera works

========================
SUCCESS CONDITION
=================

[ ] can write a working scene in <75 LOC

[ ] can:
- spawn entity
- move with WASD
- see in 3D
- not touch raw raylib much

========================
DO NOT ADD
==========

* no ECS
* no component system
* no physics engine
* no scripting
* no UI system
* no multithreading
* no “proper architecture”

========================
RULE
========================

If something takes >2 hours → too complex → simplify
