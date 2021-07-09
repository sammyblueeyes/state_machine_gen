use std::path::PathBuf;
use clap::arg_enum;
use structopt::StructOpt;

pub mod ast;

#[macro_use] extern crate lalrpop_util;

lalrpop_mod!(pub state_machine); // synthesized by LALRPOP

arg_enum! {
    #[derive(Debug)]
    enum OutputLanguage {
        Cpp,
        Rust,
    }
}

#[derive(Debug, StructOpt)]
#[structopt(name = "state_machine_gen", about = "Generate state machine framework from dot file")]
struct Opt {
    /// Activate debug mode
    #[structopt(short, long)]
    debug: bool,

    /// Select the output language
    #[structopt(short, long)]
    lang: OutputLanguage,

    /// Input file
    #[structopt(parse(from_os_str))]
    input: PathBuf,

    /// Output file, stdout if not present
    #[structopt(short = "o", long = "output", parse(from_os_str))]
    output: Option<PathBuf>,
}

fn main() {
    let opt = Opt::from_args();
    println!("{:?}", opt);

    println!("{:#?}", state_machine::DigraphParser::new().parse(r#"
digraph MyStateMachine{
    STATE_off[shape=octagon];
    STATE_ready[shape=octagon];
    STATE_ready_delay_start[shape=octagon];
    STATE_wait_delayed_start[shape=octagon];
    STATE_mixing[shape=octagon];
    STATE_first_proof[shape=octagon];
    STATE_knock_down[shape=octagon];
    STATE_second_proof[shape=octagon];
    STATE_baking[shape=octagon];
    STATE_keep_warm[shape=octagon];
    STATE_error[shape=octagon];
}
    "#))
}
