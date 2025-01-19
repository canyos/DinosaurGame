package dainosaur.dinosaurserver.service;

import dainosaur.dinosaurserver.dto.ScoreDto;
import dainosaur.dinosaurserver.entity.Score;
import dainosaur.dinosaurserver.repository.ScoreRepository;
import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.List;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
public class ScoreService {
    private final ScoreRepository scoreRepository;

    public List<Integer> getScore() {
        return scoreRepository.findHighScore();
        //return scores.stream().map(ScoreDto::fromEntity).toList();
    }

    public void addScore(ScoreDto scoreDto) {
        Score score = scoreDto.toEntity();
        //System.out.println(score.getScore());
        scoreRepository.save(score);
    }
}
