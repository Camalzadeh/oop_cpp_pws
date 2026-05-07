import pandas as pd
import chess
import subprocess
import os
import sys

def san_to_coords(moves_san, board):
    coords_moves = []
    for move_san in moves_san.split():
        try:
            move = board.parse_san(move_san)
            coords_moves.append(move.uci())
            board.push(move)
        except:
            return None # Failed to parse SAN
    return coords_moves

def run_test_game(game_id, moves):
    input_str = "\n".join(moves) + "\n/quit\n"
    try:
        process = subprocess.Popen(
            ['..\\chess.exe'], 
            stdin=subprocess.PIPE, 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE,
            text=True,
            cwd='..'
        )
        stdout, stderr = process.communicate(input=input_str, timeout=15)
        
        # Detection of failure based on error messages from our C++ program
        error_keywords = [
            "Invalid coordinates", 
            "No piece at origin", 
            "It's not your turn", 
            "Illegal move", 
            "Cannot capture", 
            "Move leaves king in check"
        ]
        
        failed = False
        reason = ""
        for kw in error_keywords:
            if kw in stdout:
                failed = True
                reason = kw
                break
        
        return failed, stdout, reason
    except Exception as e:
        return True, str(e), "Execution Error"

if __name__ == "__main__":
    if not os.path.exists('outputs'):
        os.makedirs('outputs')

    csv_path = os.path.join('archive', 'games.csv')
    if not os.path.exists(csv_path):
        print(f"Error: {csv_path} not found.")
        sys.exit(1)
        
    df = pd.read_csv(csv_path)
    total_games = len(df)
    print(f"Starting test for {total_games} games...")

    summary_file = os.path.join('outputs', 'test_summary.log')
    failures_file = os.path.join('outputs', 'test_failures.log')
    
    with open(summary_file, 'w') as f_sum, open(failures_file, 'w', encoding='utf-8') as f_fail:
        f_sum.write(f"CHESS TEST SUMMARY - TOTAL GAMES: {total_games}\n")
        f_sum.write("-" * 50 + "\n")
        
        passed_count = 0
        failed_count = 0
        
        for idx, row in df.iterrows():
            game_id = row['id']
            moves_san = row['moves']
            
            board = chess.Board()
            moves_coords = san_to_coords(moves_san, board)
            
            if moves_coords is None:
                status = "SKIPPED (SAN parse error)"
                f_sum.write(f"[{idx+1}/{total_games}] {game_id}: {status}\n")
                continue

            failed, output, reason = run_test_game(game_id, moves_coords)
            
            if failed:
                status = f"FAILED ({reason})"
                f_sum.write(f"[{idx+1}/{total_games}] {game_id}: {status}\n")
                f_fail.write(f"FAILURE IN GAME {game_id}:\nReason: {reason}\n")
                f_fail.write("Output:\n" + output + "\n")
                f_fail.write("-" * 80 + "\n")
                failed_count += 1
            else:
                status = "PASSED"
                f_sum.write(f"[{idx+1}/{total_games}] {game_id}: {status}\n")
                passed_count += 1
            
            if (idx + 1) % 10 == 0:
                print(f"Progress: {idx+1}/{total_games} | Passed: {passed_count} | Failed: {failed_count}")
                f_sum.flush()
                f_fail.flush()

        f_sum.write("\n" + "=" * 50 + "\n")
        f_sum.write(f"FINAL RESULTS: Passed: {passed_count}, Failed: {failed_count}\n")

    print(f"Testing finished. Summary: {summary_file}, Failures: {failures_file}")
