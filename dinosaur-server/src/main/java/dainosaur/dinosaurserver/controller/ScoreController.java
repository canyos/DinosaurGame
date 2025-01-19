package dainosaur.dinosaurserver.controller;

import dainosaur.dinosaurserver.dto.ScoreDto;
import dainosaur.dinosaurserver.service.ScoreService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

@Controller
@RequiredArgsConstructor
public class ScoreController {
    private final ScoreService scoreService;

    @PostMapping("/api/score")
    public ResponseEntity<?> addScore(@RequestBody ScoreDto scoreDto) {
        scoreService.addScore(scoreDto);
        return ResponseEntity.ok().build();
    }

    @GetMapping("/api/score")
    public ResponseEntity<?> getScore() {
        return ResponseEntity.ok(scoreService.getScore());
    }
}
