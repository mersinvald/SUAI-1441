extern crate sdl2;
extern crate sdl2_gfx;

use sdl2::pixels::Color;
use sdl2::event::Event;
use sdl2::keyboard::Scancode::*;

mod matrix;
mod primitives;
mod line;
use primitives::*;

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

    // Set initial lines coordinates
    let startx  = ((WIDTH/2) - 10) as f32;
    let starty1 = (HEIGHT/4)       as f32;
    let starty2 = (HEIGHT/4*3)     as f32;

    // Create lines
    let mut line1 = line::Line::new(
        Point2D::new(startx - 10.0, starty1),
        Point2D::new(startx - 10.0, starty2),
        Color::RGB(0, 255, 0)
    );

    let mut line2 = line::Line::new(
        Point2D::new(startx + 10.0, starty1),
        Point2D::new(startx + 10.0, starty2),
        Color::RGB(255, 0, 0)
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
        let mut dx = 0.0;
        let mut dy = 0.0;
        let mut scale = 1.0;
        let mut angle = 0.0;

        // Poll presed keys
        for key in events.keyboard_state().pressed_scancodes() {
            match key {
                W       => dy -= 3.0,
                S       => dy += 3.0,
                D       => dx += 3.0,
                A       => dx -= 3.0,
                Up      => scale += 0.05,
                Down    => scale -= 0.05,
                Left    => angle -= 3.0,
                Right   => angle += 3.0,
                _       => (),
            }
        }

        // Do affine transformations
        line1.translate(dx, dy);
        line1.scale(scale, scale);
        line1.rotate(angle);

        line2.translate(dx, dy);
        line2.scale(scale, scale);
        line2.rotate(angle);

        // Clear render buffer
        renderer.set_draw_color(Color::RGB(0, 0, 0));
        renderer.clear();

        // Draw lines
        line1.draw(&renderer);
        line2.draw_builtin_line(&renderer);

        // Present render buffer
        renderer.present();

        // Sleep until the next frame should be rendered
        fps_manager.delay();
    }
}
