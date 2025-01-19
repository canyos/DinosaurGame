package dainosaur.dinosaurserver.repository;

import dainosaur.dinosaurserver.entity.Score;
import java.util.List;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

@Repository
public interface ScoreRepository extends JpaRepository<Score,Long> {
    @Query(value = "Select * from score s order by s.score limit 1",nativeQuery = true)
    List<Integer> findHighScore();
}
