extern crate sdl2;
extern crate sdl2_gfx;

use sdl2::pixels::Color;
use sdl2::event::Event;
use sdl2::keyboard::Scancode::*;

mod graphics;
use graphics::primitives::*;

const WIDTH: u32 = 1280;
const HEIGHT: u32 = 720;

fn main() {
    // Initialize SDL2
    let sdl_context   = sdl2::init().unwrap();
    let video_context = sdl_context.video().unwrap();

    // Create window
    let window = video_context.window("Graphics Task 1", WIDTH, HEIGHT)
        .position_centered()
        .opengl()
        .build()
        .unwrap();

    // Get renderer binded to window
    let mut renderer = window.renderer().build().unwrap();

    // Create FPS manager to precisely control inter-frames delays
    let mut fps_manager = sdl2_gfx::framerate::FPSManager::new();
    fps_manager.set_framerate(60).unwrap();

    // Set draw color and clear the screen
    renderer.set_draw_color(Color::RGB(0, 0, 0));
    renderer.clear();
    renderer.present();

    // Get event pump
    let mut events = sdl_context.event_pump().unwrap();

    let w0 = WIDTH  as f64 / 2.0;
    let h0 = HEIGHT as f64 / 2.0;

    let mut pyramid = pyramide::Pyramide::new(
        &Point3D::new(
            w0,
            h0,
            10.0
        ),
        200.0,
        200.0,
        vec![
            Color::RGB(255, 0,   0),
            Color::RGB(0,   255, 0),
            Color::RGB(0,   0,   255),
            Color::RGB(255, 100, 100),
            Color::RGB(100, 255, 100),
            Color::RGB(100, 100, 255),
        ]
    );

    // Start main loop
    'main:
    loop {
        // If exit event passed, break the loop
        for event in events.poll_iter() {
            match event {
                Event::Quit {..} => break 'main,
                _ => ()
            }
        }

        // Initialize variables
        let mut dx = 0.0_f64;
        let mut dy = 0.0_f64;
        let mut dz = 0.0_f64;
        let mut rx = 0.0_f64;
        let mut ry = 0.0_f64;
        let mut rz = 0.0_f64;
        let mut scale = 1.0;
        let mut fill = false;

        // Poll presed keys
        for key in events.keyboard_state().pressed_scancodes() {
            match key {
                W       => rx -= 3.0,
                S       => rx += 3.0,
                D       => ry += 3.0,
                A       => ry -= 3.0,
                Q       => rz -= 3.0,
                E       => rz += 3.0,
                P       => scale += 0.01,
                O       => scale -= 0.01,
                Left    => dx -= 3.0,
                Right   => dx += 3.0,
                Up      => dy -= 3.0,
                Down    => dy += 3.0,
                M       => dz += 3.0,//scale += 0.01,
                N       => dz -= 3.0,//scale -= 0.01,
                F       => fill = true,
                _       => (),
            }
        }

        // Clear render buffer
        renderer.set_draw_color(Color::RGB(0, 0, 0));
        renderer.clear();

        // Do affine transformations and draw
        pyramid.rotate(rx, ry, rz);
        pyramid.scale(scale, scale, scale);
        pyramid.translate(dx, dy, dz);

        // Draw
        pyramid.draw(&renderer);

        if fill {
            pyramid.fill(&renderer);
        }

        // Present render buffer
        renderer.present();

        // Sleep until the next frame should be rendered
        fps_manager.delay();
    }
}