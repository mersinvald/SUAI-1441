#![feature(step_by)]

extern crate sdl2;
extern crate sdl2_gfx;

use sdl2_gfx::primitives::DrawRenderer;
use sdl2::pixels::Color;
use sdl2::event::Event;
use std::time::Duration;

mod primitives;
mod circle;

use circle::*;
use primitives::*;

const WIDTH: u32 = 1600;
const HEIGHT: u32 = 800;

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
    fps_manager.set_framerate(30).unwrap();

    // Set draw color and clear the screen
    renderer.set_draw_color(Color::RGB(0, 0, 0));
    renderer.clear();
    renderer.present();

    // Get event pump
    let mut events = sdl_context.event_pump().unwrap();

    // Set first circle center and radius
    let startx1 = (WIDTH / 100 * 25) as f32;
    let startx2 = (WIDTH / 100 * 75) as f32;
    let starty  = (HEIGHT / 2)       as f32;

    // Create circles
    let mut bresenham_circles = Vec::with_capacity(200);
    let mut builtin_circles   = Vec::with_capacity(200);

    for r in (4..).step_by(4).take(100) {
        bresenham_circles.push(
            Circle::new(
                Point2D::new(startx1, starty),
                r,
                Color::RGB(0, 255, 0)
            )
        );

        builtin_circles.push(
            Circle::new(
                Point2D::new(startx2, starty),
                r,
                Color::RGB(255, 0, 0)
            )
        );
    }

    let cache_size = 30;
    let mut bresenham_cache = [0; 30];
    let mut builtin_cache   = [0; 30];
    let mut frame_counter   = 0;

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

        // Clear render buffer
        renderer.set_draw_color(Color::RGB(0, 0, 0));
        renderer.clear();

        // Plot circles
        let (d1, d2) = draw_circles(&bresenham_circles, &builtin_circles, &renderer);

        bresenham_cache[frame_counter % 30] = d1;
        builtin_cache[frame_counter % 30] = d2;

        // Calculate average time
        let bresenham_avg = bresenham_cache.iter().fold(0, |sum, &val| {sum + val}) / cache_size;
        let builtin_avg   = builtin_cache.iter().fold(0, |sum, &val| {sum + val}) / cache_size;

        // Draw text
        draw_text(bresenham_avg, builtin_avg, &renderer);

        // Present render buffer
        renderer.present();

        // Sleep until the next frame should be rendered
        fps_manager.delay();
        frame_counter += 1;
    }
}

fn draw_circles(bresenham: &Vec<Circle>, builtin: &Vec<Circle>,
            renderer: &sdl2::render::Renderer) -> (u32, u32) {
    // Plot circles
    let builtin_duration = stopwatch(|| {
        for c in builtin {
            c.draw_builtin_circle(&renderer);
        }
    });

    let bresenham_duration = stopwatch(|| {
        for c in bresenham {
            c.draw(&renderer);
        }
    });

    (bresenham_duration.subsec_nanos(), builtin_duration.subsec_nanos())
}

fn draw_text(bresenham: u32, builtin: u32, renderer: &sdl2::render::Renderer) {
    let faster = if bresenham > builtin {
        "BUILTIN"
    } else {
        "MY IMPLEMENTATION"
    };

    let x = WIDTH as i16 - 300;
    let y = 10;

    // Draw results
    renderer.string(
        x,
        y,
        &format!("Bresenham: {} ms", bresenham / 1000_000),
        Color::RGB(255, 255, 255)
    ).unwrap();

    renderer.string(
        x,
        y + 20,
        &format!("Builtin:   {} ms", builtin / 1000_000),
        Color::RGB(255, 255, 255)
    ).unwrap();

    renderer.string(
        x,
        y + 40,
        &format!("Faster: {}", faster),
        Color::RGB(255, 255, 255)
    ).unwrap();
}

fn stopwatch<F>(mut closure: F) -> Duration
    where F: FnMut() {
    use std::time::SystemTime;
    let before_time = SystemTime::now();
    closure();
    let after_time  = SystemTime::now();
    after_time.duration_since(before_time).unwrap()
}
