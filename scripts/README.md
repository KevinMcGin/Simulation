# Scripts
Scripts are to be run from this `scripts` directory.
Run with `-h` for information on the flags for each script.

## Build & Compile
``./compile.sh -v``

## Test
### All Tests
``./test.sh``

### CPU Tests Only
``./test.sh -c``

## Run Engine
``./engine.sh``

## Run Server
``./server.sh``

Start the server through this script rather than running the
``SimulationEngineServer`` binary directly.

The script exports ``SIMULATION_USE_GPU`` from ``config/project.config``.
Run the binary on its own and that variable is unset, which
``Universe::Universe`` treats as ``true`` — so a CPU-only build runs the GPU
laws, which on such a build are the do-nothing mocks in
``SimulationEngineLib/gpuMock``. Nothing fails and nothing warns: every
request still answers 200 with a full set of frames in which no particle has
moved from where it started.

If you do need to run the binary directly, set the variable yourself:

``SIMULATION_USE_GPU=false ./builds/build/bin/SimulationEngineServer``

Check the engine's first lines of output either way — it prints
``Running on CPU`` or ``Running on GPU`` before each simulation.

## Run Renderer
``./render.sh``
